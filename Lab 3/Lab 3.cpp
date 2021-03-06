// Lab 3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <omp.h>
#include <stdio.h>

#define n 100

int main(int argc, char* argv[])
{
	int a[n], b[n], c, i, rez, partial_sum = 0;

	double s = 0, e = 0;

	omp_set_num_threads(4);

	rez = 0;

	for (i = 0; i < n; i++)
	{
		a[i] = i;
		b[i] = 2;
	}

	s = omp_get_wtime();
	for (i = 0; i < n; i++)
		rez += a[i] * b[i];
	e = omp_get_wtime();

	printf_s("Sequential: %d, this operation took: %3f\n", rez, e - s);

	rez = 0;
	
	//parallel without reduction
	s = omp_get_wtime();
	#pragma omp parallel private(partial_sum)
	{
		partial_sum = 0;
		#pragma omp for
		for (i = 0; i < n; i++)
			partial_sum += a[i] * b[i];

		#pragma omp critical 
		{
			rez += partial_sum;
		}
	}
	e = omp_get_wtime();

	printf_s("Without reduction: %d, this operation took: %3f\n", rez, e-s);

	rez = 0;

	s = omp_get_wtime();
	// parallel with reduction
	#pragma omp parallel
	{
		#pragma omp for reduction(+:rez)
			for (i = 0; i < n; i++)
			{
				rez += a[i] * b[i];
			}

			//printf_s("Thread %d: %d", omp_get_thread_num(), rez);
	}
	e = omp_get_wtime();

	printf_s("With reduction: %d, this operation took: %3f\n", rez, e-s);

    return 0;
}

