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
    // Parameters
    int N = 512; // Number of samples
    double fs = 250; // Sample rate [Hz]

    // Calculated parameters
    double ts = 1/fs; // Sample time, [s]
    double T0 = N*ts; // Fundamental period [s]

    printf("Number of samples: %d\n", N);
    printf("Fundamental period: %0.2f s\n", T0);
    printf("Sampling rate: %0.2f Hz\n", fs);
    printf("Sampling time: %0.2f s\n", ts);
    printf("------------------------------------------------\n");

    double signal[N];
    for (int i = 0; i < N; ++i) {
        signal[i] = generate_signal(ts*i);
        printf("Signal at t = %0.2f: %0.2f\n", ts*i, signal[i]);
    }


    // Calculate DFT
    printf("Calculating DFT\n");
    printf("------------------------------------------------\n");
    complex dft[N];
    for (int n = 0; n < N; ++n) {
        dft[n] = 0;
        for (int k = 0; k < N; ++k) {
            dft[n] += signal[k]*cexp(-I*2*PI/N*n*k);
        }
        if (n == 0) {
            printf("F[%0.2f Hz] = %f\n", fs/N*n, cabs(dft[n])/N);
        } else if (fs/N*n < fs/2){
            printf("F[%0.2f Hz] = %f\n", fs/N*n, 2*cabs(dft[n])/N);
        }
    }
    printf("------------------------------------------------\n");

    return 0;
}

double generate_signal(double t)
{
    /*return 5 + 2*cos(2*PI*t - PI/2) + 3*cos(4*PI*t);*/
    return 21 + 2*cos(2.5*2*PI*t - PI/2) + 5*sin(0.25*4*PI*t) + 30*cos(120*2*PI*t);
}
