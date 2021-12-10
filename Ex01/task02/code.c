#include <stdio.h>

/**
* Calculates the sum of all 2nd columns of a 3-dimensional array.
* 
* @param *cubePtr an integer pointer, points to the first element of the 3d array
* @param dim1 an integer, the 1st dimension of the 3-dimensional array
* @param dim2 an integer, the 2nd dimension of the 3-dimensional array
* @param dim3 an integer, the 3rd dimension of the 3-dimensional array
* @return sum an integer, the sum of all integers found in the 2nd column of the 3d array
*/
int sum2nd(int *cubePtr, int dim1, int dim2, int dim3) {
	int sum = 0;
	int *lastPtr;
	lastPtr = cubePtr + dim1*dim2*dim3;
	sum = *(cubePtr + 1);
	cubePtr++;
	while ( (cubePtr+dim3) < lastPtr ) {
		sum += *(cubePtr + dim3);
		cubePtr += dim3;
	}  
	return sum;
}

/**
* Prints out the sums of the 2nd columns of the 3-dimensional arrays 
* cube1 and cube2 respectively.
*
* @return 0 if successful
*/
int main(void) {
	int cube1[3][2][4] = { {{1,2,3,4}},
                         	{{2,3}, {4,6,8,10}},
                         	{{3,4,5,6}, {6,8,10}} };

	int cube2[2][3][3] = { {{9,8,7}, {6}, {5,4}},
                         	{{3,2}, {1,2,3}, {4}} };
	
	printf("%d\n", sum2nd(&cube1[0][0][0], 3,2,4) );
	printf("%d\n", sum2nd(&cube2[0][0][0], 2,3,3) );

	return 0;
}


