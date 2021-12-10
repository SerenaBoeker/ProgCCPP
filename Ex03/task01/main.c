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
 * @brief Scales an image by applying a billinear interpolation filter.
 *
 * @param in pixel data of input image
 * @param out  pixel data of output image. Has to be pre allocated.
 * @param src_sz the size of the input image
 * @param trgt_sz the desired output size.
 */
void resize_image(pixel_rgb_t *in, pixel_rgb_t *out, image_size_t src_sz, image_size_t trgt_sz) {

#warning Task 3: Write your code here.

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
        pixel_rgb_t *pixelData_src = NULL;
		image_size_t oldImageSize;

		while ( (option_index = getopt(argc, argv, "i:o:")) != -1) {
			switch (option_index) {
				case 'i':
						inputFile = optarg;
						break;
				case 'o':
						outputFile = optarg;
						break;
				default:
						fprintf(stderr, "Usage: %s -i inputfilename.jpeg -o outputfilename.jpeg\n", argv[0]);
						exit(EXIT_FAILURE);
			}
		}

		load_jpeg(inputFile, &pixelData_src, &oldImageSize);
		save_jpeg(pixelData_src, oldImageSize, outputFile);
        free(pixelData_src);

    return 0;
}
