#include <stdio.h>

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

int main(void) {
	int cube1[3][2][4] = { {{1,2,3,4}},
                         	{{2,3}, {4,6,8,10}},
                         	{{3,4,5,6}, {6,8,10}} };

	int cube2[2][3][3] = { {{9,8,7}, {6}, {5,4}},
                         	{{3,2}, {1,2,3}, {4}} };
                         
	for(int i=0; i<3; i++) {
		for(int j=0; j<2; j++) {
			for(int k=0; k<4; k++) {
				printf("address of cube1[%d][%d][%d] = %p\n", i, j, k, &cube1[i][j][k]);
			}
		}
	}
	
	printf("sum of 2nd column of cube1 (should be 23): %d\n", sum2nd(&cube1[0][0][0], 3,2,4) );
	printf("sum of 2nd column of cube2 (should be 16): %d\n", sum2nd(&cube2[0][0][0], 2,3,3) );

	return 0;
}


