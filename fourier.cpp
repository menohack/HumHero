#include "fourier.h"

void add_sine(fftw_complex * input, int length, double frequency)
{
	int i;
	for (i=0; i < length; i++)
		input[i][0] += sin(2.0 * M_PI * (frequency * i/(length)));
}

void make_input(fftw_complex * input, int length)
{
	int i;
	for (i=0; i < length; i++)
	{
		input[i][0] = 0.0;
		input[i][1] = 0.0;
	}

	add_sine(input, length, 2.0);
	add_sine(input, length, 17.0);
	add_sine(input, length, 6.0);

}
	

void print_result(fftw_complex * output, int length)
{
	int i = 0;
	for (; i < length; i++)
		if (output[i][0] > 0.001 || output[i][1] < -0.001)
			printf("%d: {%f,%f} ", i, output[i][0], output[i][1]);

	printf("\n");
}

void run_fourier(fftw_complex * in, fftw_complex * out, int N)
{
	fftw_plan p;

	
    //make_input(in, N);
	//print_result(in, N);
	
    p = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
	fftw_execute(p); /* repeat as needed */

	//print_result(out, N);

    //double * outfile = new double[N];
    //int i;
    //for (i=0; i < N; i++)
    //    outfile[i] = *in[i][0];
		//printf("%f\n", in[i][0]);


	fftw_destroy_plan(p);


}

void fourier_free(fftw_complex * in, fftw_complex * out)
{
    fftw_free(in); fftw_free(out);
}
