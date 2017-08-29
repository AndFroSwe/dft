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
    int N = 9; // Number of samples
    /*double Ts = 0.75; // Sampling period*/
    double Ts = 1.5; // Sampling period, s
    double ts = Ts/(N - 1); // Time between samples, s

    printf("Number of samples: %d\n", N);
    printf("Sampling period: %0.2f s\n", Ts);
    printf("Sampling rate: %0.2f Hz\n", 1/ts);
    printf("Sampling time: %0.2f s\n", ts);
    printf("------------------------------------------------\n");

    double signal[N];
    for (int i = 0; i < N; ++i) {
        signal[i] = generate_signal(ts*i);
        printf("Signal at t = %0.2f: %0.2f\n", ts*i, signal[i]);
    }


    // Calculate DFT
    printf("Calculating DFT\n");
    complex dft[N];
    for (int n = 0; n < N; ++n) {
        dft[n] = 0;
        for (int k = 0; k < N; ++k) {
            dft[n] += signal[k]*cexp(-I*2*PI/N*n*k);
        }
        printf("F[%d] = %f\n", n, cabs(dft[n])/N);
    }



    return 0;
}

double generate_signal(double t)
{
    return 5 + 2*cos(2*PI*t - PI/2) + 3*cos(4*PI*t);
}
