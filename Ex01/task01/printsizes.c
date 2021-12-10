#include <stdio.h>

/** 
* Prints the name of the simple data types char, short, int, long,
* long long, float, double, long double and pointer, followed by
* their sizes in bytes.
*
* @return 0 if successful
*/ 
int main(void) {
	printf("char %d\n", (int) sizeof(char));
	printf("short %d\n", (int) sizeof(short));
	printf("int %d\n", (int) sizeof(int));
	printf("long %d\n", (int) sizeof(long));
	printf("long long %d\n", (int) sizeof(long long));
	printf("float %d\n", (int) sizeof(float));
	printf("double %d\n", (int) sizeof(double));
	printf("long double %d\n", (int) sizeof(long double));
	printf("pointer %d\n", (int) sizeof(void*));
	return 0;
}
