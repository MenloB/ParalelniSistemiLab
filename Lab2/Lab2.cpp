// Lab2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <mpi.h>

#define n 4
#define m 3

#pragma comment(lib, "msmpi.lib")

// (rank +/- 2) % m


int main(int argc, char* argv[])
{
	int rank, size;
	MPI_Comm comm;
	int dim[2], period[2], reorder;
	int coord[2];
	int errs = 0;
	int left, right;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank); // current rank
	MPI_Comm_size(MPI_COMM_WORLD, &size); // size

	if (size != 12)
	{
		printf("Please run with 12 processes.\n");
		fflush(stdout);
		MPI_Abort(MPI_COMM_WORLD, 1);
	}

	dim[0] = n;
	dim[1] = m;
	period[0] = 0;
	period[0] = 1;
	reorder = 0;

	MPI_Cart_create(MPI_COMM_WORLD, 2, dim, period, reorder, &comm);
	// size - n - 1

	MPI_Cart_shift(comm, 1, 2, &left, &right);

	printf("Komsije za proces %d su: levi: %d i desni: %d", rank, left, right);

	MPI_Comm_free(&comm);

	MPI_Finalize();

    return 0;
}

