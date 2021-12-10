#include <stdio.h>

/**
* Counts the length of a passed string with an index using a while-loop,
* which searches for the end of the word (null).
* 
* @param *string a char pointer, points to the passed string
* @return index an integer, the length of the passed string
*/
int intIndexStrLength(char *string) {
	int index = 0;
	while(*string) {
		index++;
		*(string++);
	}
	return index;
}

/**
* Calculates the length of a passed string using pointer arithmetic.
* Through the while-loop the temporary pointer will point to the null
* element at the end of the string so that the difference between the 
* temporary pointer and the string pointer delivers the string length.
*
* @param *string a char pointer, points to the passed string
* @return length an integer, the calculated length of the passed string
*/
int ptrArithmStrLength(char *string) {
	char *temp;
	temp = string;
	while(*temp) {
		temp++;
	}
	int length = temp-string;		
	return length;
}

/**
* Main function, prints "wrong input" if more or less than one command
* line argument are provided or the length of the provided string if
* exactly one command line argument is given.
*
* @param argc an integer, contains the number of the elements in the array argv[]
* @param *argv[] char array of pointers, contains program name and command line
*		  arguments, if given
* @return 0 if successfull
*/
int main (int argc, char *argv[]) {
	if ( argc==2 ) {
		printf("%d\n", intIndexStrLength(argv[1]) );
		printf("%d\n", ptrArithmStrLength(argv[1]) );
	} else {
		printf("wrong input\n");
	}
	return 0;
}
