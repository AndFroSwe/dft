/* File: dft.c
 * Author: andfro
 */

#include "dft.h"

int main(int argc, char *argv[])
{
    printf("Hello World!\n");

    for (int i = 0; i < 4; ++i)
    {
        double val = sin(2*3.14*0.04*i);
        printf("Sample %d = %f\n", i, val);
    }


    return 0;
}
