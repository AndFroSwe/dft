/* File: dft.c
 * Author: andfro
 */

/*#include "dft.h"*/
#include <complex.h>
#include <stdio.h> 
#include <math.h>
#include <stdlib.h>

#define PI 3.141592654

typedef struct sample_data
{
    /* Circular buffer, design to efficiently hold data used to calc DFT. 
     * FIFO implementation.
     */
    double *buffer;     // Start of data buffer
    double *buffer_end; // End of data buffer
    double *data_end;   // End of ring buffer
    unsigned int size;  // Size of data buffer (number of samples)
    double fs;    // Sample rate [Hz]
} sample_data;

void init_sample_data(sample_data *sd, unsigned int size, double fs)
{
    sd->buffer = malloc(sizeof(double)*size);
    sd->buffer_end = sd->buffer + size;
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
    if (sd->data_end == (sd->buffer_end))
    {
        sd->data_end = sd->buffer;
    }
    
}

void calculate_dft(sample_data *sd, complex *result)
{
    /* Calculates dft from sample data
     */
    int N = sd->size;
    double *p = sd->data_end;

    for (int n = 0; n < N; ++n) {
        result[n] = 0;
        int k = 0;
        do {
            result[n] += *(--p)*cexp(-I*2*PI/N*n*k);
            k++;
            // Wrap around guard
            if (p == sd->buffer_end + 1) {
                p = sd->buffer;
            }
        } while(p != sd->data_end);
    }
}
void print_data(const sample_data *sd)
{
    double *p = sd->data_end;
    printf("{");
    do {
        printf("%0.2f ", *p);
        ++p;
        if (p == (sd->buffer_end)) {
            p = sd->buffer;
        }
    } while(p != sd->data_end);
    printf("}\n");
}

double generate_signal(double t)
{
    return 5 + 2*cos(2*PI*t - PI/2) + 3*cos(4*PI*t);
    /*return 21 + 2*cos(2.5*2*PI*t - PI/2) + 5*sin(0.25*4*PI*t) + 30*cos(120*2*PI*t);*/
}
int main(int argc, char *argv[])
{
    unsigned int s = 4;
    double hz = 4.0;
    printf("Create\n");
    printf("Init\n");
    sample_data *sd = malloc(sizeof(sample_data));
    init_sample_data(sd, s, hz);
    printf("Add\n");
    for (int i = 0; i < s; ++i) {
        printf("%f\n",generate_signal(i/hz));
        add_data(sd, generate_signal(i/hz));
    }

    print_data(sd);
    free_sample_data(sd);
    free(sd);


    return 0;
}
