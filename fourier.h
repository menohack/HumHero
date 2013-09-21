#ifndef FOURIER_H
#define FOURIER_H

#include <fftw3.h>
#include <math.h>

void add_sine(fftw_complex * input, int length, double frequency);
void make_input(fftw_complex * input, int length);
void print_result(fftw_complex * output, int length);
void run_fourier(fftw_complex * in, fftw_complex * out, int N);
void fourier_free(fftw_complex * in, fftw_complex * out);

#endif // FOURIER_H
