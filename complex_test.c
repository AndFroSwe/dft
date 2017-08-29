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
    int N = 4; // Number of samples
    double T = 3.0/4; // Sampling period

    printf("Number of samples: %d\n", N);
    double signal[N];
    for (int i = 0; i < N; ++i) {
        double t = (double)i*2*PI/N/T;
        signal[i] = generate_signal(t);
        printf("Signal at t = %0.2f: %0.2f\n", t, signal[i]);
    }


    // Calculate DFT
    printf("Calculating DFT\n");
    complex dft[N];
    for (int n = 0; n < N; ++n) {
        dft[n] = 0;
        for (int k = 0; k < 4; ++k) {
            dft[n] += signal[k]*cexp(-I*PI/2.0*n*k);
        }
        printf("F[%d] = %f\n", n, cabs(dft[n]));
    }



    return 0;
}

double generate_signal(double t)
{
    return 5 + 2*cos(2*PI*t - PI/2) + 3*cos(4*PI*t);
}
