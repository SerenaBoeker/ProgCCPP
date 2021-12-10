#include <stdio.h>
#include <math.h>

void main(int argc, char *argv[]) {

    int x = 310, y = 157;
    float div = ((float) x) / ((float) y);
    printf("x/y = %f\n", div);
    int intRatio = roundf(div);
    printf("intRatio: %d\n", intRatio);

    return 0;
}