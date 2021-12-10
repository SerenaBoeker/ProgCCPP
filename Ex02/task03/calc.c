#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
	int num1;
	int num2;
	char op;
	char input[100];
	
	do {
		printf("Enter <int> <op> <int>, single '0' to exit: ");
		fgets(input, 99, stdin);
		
		if(strlen(input) == 2 && input[0]=='0') {
			printf("Goodbye!\n");
			break;
		}
		
		if (sscanf(input, "%d %c %d", &num1, &op, &num2) != 3) {
			printf("invalid input\n");
		}
		
		if (sscanf(input, "%d %c %d", &num1, &op, &num2) == 3) {
			switch (op) {
				case '+':
					printf("%d %c %d = %d\n", num1, op, num2, (num1+num2));
					break;
				case '-':
					printf("%d %c %d = %d\n", num1, op, num2, (num1-num2));
					break;
				case '*':
					printf("%d %c %d = %d\n", num1, op, num2, (num1*num2));
					break;
				case '/':
					if (num2 == 0) {
						printf("You cannot divide by 0!\n");
					} else {
						printf("%d %c %d = %d\n", num1, op, num2, (num1/num2));
					}
					break;
				default:
					printf("\"%c\" is none of the accepted operators (+-*/)\n", op);
			}
		}
		
	} while (1);
	
	return 0;
}
