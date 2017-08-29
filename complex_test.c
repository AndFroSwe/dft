#include <complex.h>
#include <stdio.h>
#include <math.h>

#define PI 3.141592654

double generate_signal(double);

int main(int argc, char *argv[])
{
    printf("Starting program\n");
    printf("Generating signal\n");

    // Get signal samples
    double signal[4];
    for (int i = 0; i < 4; ++i) {
        double t = (double)i/4;
        signal[i] = generate_signal(t);
        printf("Signal at t = %0.2f: %0.2f\n", t, signal[i]);
    }


    // Calculate DFT
    printf("Calculating DFT\n");
    complex dft[4];
    for (int n = 0; n < 4; ++n) {
        for (int N = 0; N < 4; ++N) {
            dft[n] += signal[N]*cexp(-I*PI/2.0*n*N);
        }
        printf("F[%d] = %f\n", n, cabs(dft[n]));
    }



    return 0;
}

double generate_signal(double t)
{
    return 5 + 2*cos(2*PI*t - PI/2) + 3*cos(4*PI*t);
}
