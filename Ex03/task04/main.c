#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <jpeglib.h>
#include <stdbool.h>
#include <getopt.h>

/**
 * @brief Contains color data for a single pixel.
 */
struct pixel_rgb_t {
	unsigned char red;
	unsigned char green;
	unsigned char blue;
};

/**
 * @brief Defines an image size.
 */
struct image_size_t {
    unsigned int width;
    unsigned int height;
};

typedef struct pixel_rgb_t pixel_rgb_t;
typedef struct image_size_t image_size_t;

/**
* @brief Estimates a new value using the mathematical formula for the bilinear interpolation
*
* @param p00 top-left value
* @param p10 top-right value
* @param p01 bottom-left value
* @param p11 bottom-right value
* @param dx distance from the values on the left
* @param dy distance from the values on the right
* @return pxy the result
*/
unsigned char bilinear_interpolation(unsigned char p00, unsigned char p10, 
							unsigned char p01, unsigned char p11,
							float dx, float dy) {
	unsigned char pxy = 0;
	pxy += p00 * (1-dx) * (1-dy);
	pxy += p10 * dx * (1-dy);
	pxy += p01 * (1-dx) * dy;
	pxy += p11 * dx * dy;
	return pxy;
}

/**
 * @brief Scales an image by applying a billinear interpolation filter.
 *
 * @param in pixel data of input image
 * @param out  pixel data of output image. Has to be pre allocated.
 * @param src_sz the size of the input image
 * @param trgt_sz the desired output size.
 */
void resize_image(pixel_rgb_t *in, pixel_rgb_t *out, image_size_t src_sz, image_size_t trgt_sz) {

	float xRatio = ((float)src_sz.width) / ((float) trgt_sz.width);
	float yRatio = ((float)src_sz.height) / ((float) trgt_sz.height);
	
	int x, y;
	float dx, dy;
	pixel_rgb_t p00, p01, p10, p11, outputPixel;
	size_t inputIndex, outputIndex = 0;

	for (unsigned int i = 0; i < trgt_sz.height; i++) {
		for (unsigned int j = 0; j < trgt_sz.width; j++) {
			// mapping the new pixels to the initial pixels from source image;
			// has to be an integer value
			x = (int) (j * xRatio);
			y = (int) (i * yRatio);

			// distances of the "new" pixels from the "old" pixels
			// ("new" pixels are inbetween the "old pixels")
			dx = (j * xRatio) - x;
			dy = (i * yRatio) - y;

			// the index for the input pixel data
			inputIndex = x + src_sz.width * y;

			// identifying the pixels needed for the billinear interpolation
			p00 = in[inputIndex];
			p01 = in[inputIndex + src_sz.width];
			p10 = in[inputIndex + 1];
			p11 = in[inputIndex + src_sz.width + 1];

			// calculating the new r, g, b values
			outputPixel.red   = bilinear_interpolation(p00.red,   p10.red,   p01.red,   p11.red,   dx, dy);
			outputPixel.green = bilinear_interpolation(p00.green, p10.green, p01.green, p11.green, dx, dy);
			outputPixel.blue  = bilinear_interpolation(p00.blue,  p10.blue,  p01.blue,  p11.blue,  dx, dy);

			// saving the new pixel to the resized image
			out[outputIndex] = outputPixel;
			outputIndex++;
		}
	}
}

/**
 * @brief Loads pixels from a JPEG file into memory.
 * @param name the path of the file to read
 * @param img pointer to pixel data. Will be allocated.
 * @param size the size of the image. Will be set by this function
 */
void load_jpeg(const char *name, pixel_rgb_t **img, image_size_t *const size) {
    uint8_t r, g, b;
    int width, height;
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;

    FILE *infile;
    JSAMPARRAY pJpegBuffer;
    int row_stride;
    if ((infile = fopen(name, "rb")) == NULL) {
        fprintf(stderr, "can't open %s\n", name);
        exit(1);
    }
    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);
    jpeg_stdio_src(&cinfo, infile);
    (void) jpeg_read_header(&cinfo, TRUE);
    (void) jpeg_start_decompress(&cinfo);
    width = cinfo.output_width;
    height = cinfo.output_height;

    *img = calloc((size_t) width * height, sizeof(pixel_rgb_t));
    pixel_rgb_t *current_pixel = *img;
    if (!*img) {
        printf("NO MEM FOR JPEG CONVERT!\n");
        exit(1);
    }

    row_stride = width * cinfo.output_components;
    pJpegBuffer = (*cinfo.mem->alloc_sarray)
            ((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);

    while (cinfo.output_scanline < cinfo.output_height) {
        (void) jpeg_read_scanlines(&cinfo, pJpegBuffer, 1);
        for (int x = 0; x < width; x++) {
            r = pJpegBuffer[0][cinfo.output_components * x];
            if (cinfo.output_components > 2) {
                g = pJpegBuffer[0][cinfo.output_components * x + 1];
                b = pJpegBuffer[0][cinfo.output_components * x + 2];
            } else {
                g = r;
                b = r;
            }

            //r, g and b contain the color information for the channels read, green and blue
            // current_pixel is your current pixel to fill with info from the jpeg.

			// Assign to each struct member of the current pixel_rgb_t struct
			//  the according values of r, g and b
			(*current_pixel).red = r;
			(*current_pixel).green = g;
			(*current_pixel).blue = b;

            current_pixel++;
        }
    }
    fclose(infile);
    (void) jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);

    size->height = (uint32_t) height;
    size->width = (uint32_t) width;
}

/**
 * @brief Writes pixel data to a JPEG file with 80% quality and defined image size.
 * @param pixel_data the pixel to compress
 * @param size the size of this image
 * @param filename paht to write this file to.
 */
void save_jpeg(const pixel_rgb_t *pixel_data, const image_size_t size, const char *filename) {
    FILE *outfile = fopen(filename, "wb");

    if (!outfile) {
        fprintf(stderr, "can't open %s\n for write", filename);
        exit(1);
    }

    struct jpeg_compress_struct jpeg_info;
    struct jpeg_error_mgr jpeg_error;

    jpeg_info.err = jpeg_std_error(&jpeg_error);
    jpeg_create_compress(&jpeg_info);
    jpeg_stdio_dest(&jpeg_info, outfile);

    jpeg_info.image_width = size.width;
    jpeg_info.image_height = size.height;
    jpeg_info.input_components = 3;
    jpeg_info.in_color_space = JCS_RGB;

    jpeg_set_defaults(&jpeg_info);
    jpeg_set_quality(&jpeg_info, 80, true);
    jpeg_start_compress(&jpeg_info, true);

    JSAMPROW row_pointer;

    pixel_rgb_t p;

    unsigned char *row = malloc(sizeof(unsigned char) * 3 * size.width);

    while (jpeg_info.next_scanline < jpeg_info.image_height) {

        //current is your current scanline to fill with information.
        unsigned char *current = row;

        //this is the index of the beginning of the current row in your source array.
        unsigned int current_row = jpeg_info.next_scanline * size.width;

		// For each pixel of the current row of the image
		// save the r, g, b values to the byte *current points to of the new scanline.
		// At the end of the row, size.width has been reached, so the for-loop is exited
		// and the next row of the image will be written with the next iteration of the while-loop
		for (int i = 0; i < size.width; i++) {
			p = pixel_data[current_row + i];
			*current = p.red;
			current++;
			*current = p.green;
			current++;
			*current = p.blue;
			current++;
		}


        row_pointer = (JSAMPROW) row;
        jpeg_write_scanlines(&jpeg_info, &row_pointer, true);
    }

    free(row);

    jpeg_finish_compress(&jpeg_info);
}

int main(int argc, char **argv) {
		int option_index = 0;
		char *inputFile = NULL;
		char *outputFile = NULL;
		image_size_t newImageSize = {0, 0};
		long newHeight = 0, newWidth = 0;
		char *endptr;
		pixel_rgb_t *pixelData_src = NULL;
		pixel_rgb_t *pixelData_trgt = NULL;
		image_size_t oldImageSize;

		while ( (option_index = getopt(argc, argv, "i:o:h:w:")) != -1) {
			switch (option_index) {
				case 'i':
						inputFile = optarg;
						break;
				case 'o':
						outputFile = optarg;
						break;

						// Using strtol() to convert the strings with the passed numbers to integers
						// Passed numbers must be in the value range of unsigned int (0 to 4294967295)
						// if not, print error message and exit with code 1
				case 'h':
						newHeight = strtol(optarg, &endptr, 10);

						// checking if passed parameter is not empty or contains
						// other characters than a number
						if ( (endptr == optarg) || (*endptr != '\0') ) {
								fprintf(stderr, "Invalid height parameter!\n");
								return 1;
						}

						// passed parameter must be in value range of unsigned int
						if ( 0 < newHeight && newHeight < 4294967295) {
								newImageSize.height = newHeight;
						} else {
								fprintf(stderr, "New height cannot be negative or greater than 4294967295!\n");
								return 1;
						}
						break;
				case 'w':
						newWidth = strtol(optarg, &endptr, 10);

						// checking if passed parameter is not empty or contains
						// other characters than a number
						if ( (endptr == optarg) || (*endptr != '\0') ) {
								fprintf(stderr, "Invalid width parameter!\n");
								return 1;
						}

						// passed parameter must be in value range of unsigned int
						if ( 0 < newWidth && newWidth < 4294967295) {
								newImageSize.width = newWidth;
						} else {
								fprintf(stderr, "New width cannot be negative or greater than 4294967295!\n");
								return 1;
						}
						break;
				default:
						fprintf(stderr, "Usage: %s -i inputfilename.jpeg -o outputfilename.jpeg -h newHeight -w newWidth\n", argv[0]);
						return 1;
			}
		}

		// if any of the input or outputfiles are missing, or neither a new height nor a new width
		// has been passed, print an error and exit with code 1
		if (inputFile == NULL || outputFile == NULL || (newHeight == 0 && newWidth == 0)) {
				fprintf(stderr, "Usage: %s -i inputfilename.jpeg -o outputfilename.jpeg -h newHeight -w newWidth\n", argv[0]);
				return 1;
		}

		load_jpeg(inputFile, &pixelData_src, &oldImageSize);

		// checks if either no height or no width has been passed
		// and calculates the missing height or width proportional to 
		// the passed argument
		if (newImageSize.height == 0) {
			float ratio = ((float) oldImageSize.width) / newImageSize.width;
			newImageSize.height = ((float) oldImageSize.height) / ratio;
		} else if (newImageSize.width == 0) {
			float ratio = (float) oldImageSize.height / newImageSize.height;
			newImageSize.width = (float) oldImageSize.width / ratio;
		}

		// need to allocate memory for the new scaled image depending on its new height and width
		pixelData_trgt = calloc((size_t) newImageSize.width * newImageSize.height, sizeof(pixel_rgb_t));
		if(!pixelData_trgt) {
			printf("No memory for target pixel data!\n");
			exit(1);
		}
		
		resize_image(pixelData_src, pixelData_trgt, oldImageSize, newImageSize);
		save_jpeg(pixelData_trgt, newImageSize, outputFile);
		free(pixelData_src);
		free(pixelData_trgt);

    return 0;
}
