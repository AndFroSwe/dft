/* File: dft.c
 * Author: andfro
 */

/*#include "dft.h"*/
#include <complex.h>
#include <stdio.h> 
#include <math.h>
#include <stdlib.h>

typedef struct sample_data
{
    double *buffer;     // Start of data buffer
    double *buffer_end; // End of data buffer
    double *data_start; // Start of ring buffer
    double *data_end;   // End of ring buffer
    unsigned int size;  // Size of data buffer (number of samples)
    unsigned int fs;    // Sample rate [Hz]
} sample_data;

void init_sample_data(sample_data *sd, unsigned int size, unsigned int fs)
{
    sd->buffer = malloc(sizeof(double)*size);
    sd->buffer_end = sd->buffer + size;
    sd->data_start = sd->buffer;
    sd->data_end = sd->buffer;
    sd->size = size;
    sd->fs = fs;
}

void free_sample_data(sample_data *sd)
{
    free(sd->buffer);
}

void add_data(sample_data *sd, double d)
{
    // Add data to circular buffer
    *sd->data_end = d; // Add data
    (sd->data_end)++; // Increase index of buffer
    // Check if buffer filled
    if (sd->data_end == sd->buffer_end)
    {
        sd->data_end = sd->buffer;
    }
    
}

void print_data(const sample_data *sd)
{
    double *p = sd->data_end;
    printf("{");
    do {
        printf("%0.2f ", *(--p));
        if (p == sd->buffer) {
            p = sd->buffer_end;
        }
    } while(p != sd->data_end);
    printf("}\n");
}

int main(int argc, char *argv[])
{
    unsigned int s = 32;
    printf("Create\n");
    printf("Init\n");
    sample_data *sd = malloc(sizeof(sample_data));
    init_sample_data(sd, s, 1);
    printf("Size: %d \n", sd->size);
    printf("Add\n");
    for (int i = 0; i < s + 100; ++i) {
        add_data(sd, i);
    }

    print_data(sd);
    free_sample_data(sd);
    free(sd);


    return 0;
}
