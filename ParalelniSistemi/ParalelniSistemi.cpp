// ParalelniSistemi.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdlib>
#include <mpi.h>
#define n 5

#pragma comment(lib, "msmpi.lib")


int main(int argc, char* argv[])
{
	int rank;
	float A[n][n];
	MPI_Status status;
	MPI_Datatype column_mpi_t;
	float rez;
	int p;
	int i, j;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &p);

	MPI_Type_vector(n/2, n/p, n*2, MPI_FLOAT, &column_mpi_t);
	MPI_Type_commit(&column_mpi_t);

	if (rank == 0)
	{
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				//generise nasumicne vrednosti od 0.0 do 100.0
				A[i][j] = (float) static_cast <float> (rand() / static_cast <float> (RAND_MAX / 100));

		printf("[P%d]\n: ", rank);
		printf("======================== Generisana Matrica: ========================\n");

		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				printf("%3.1f ", A[i][j]);
			}
			printf("\n");
		}

		for(i = 0, j = 1; i < n, j < p; i+=1, j++)
			MPI_Send(&(A[0][i]), 1, column_mpi_t, j, 0, MPI_COMM_WORLD);

		printf("\n");
	}
	else { /* my_rank = 1 */

		printf("[P%d]:\n ", rank);

		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				A[i][j] = 0.0;

		MPI_Recv(&(A[0][0]), 1, column_mpi_t, 0, 0, MPI_COMM_WORLD, &status);

		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				printf("%3.1f ", A[i][j]);
			}
			printf("\n");
		}

		printf("\n");
	}

	MPI_Reduce(&(A[0][0]), &rez, 1, MPI_FLOAT, MPI_MAX, 0, MPI_COMM_WORLD);

	if (rank == 0)
	{
		printf("%d", rez);
	}

	MPI_Finalize();
	return 0;
}

