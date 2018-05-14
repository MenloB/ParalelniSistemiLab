// Lab2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <mpi.h>

#pragma comment(lib, "msmpi.lib")


int main(int argc, char* argv[])
{
	int rank, size;
	MPI_Comm comm;
	int dim[2], period[2], reorder;
	int coord[2], id;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank); // current rank
	MPI_Comm_size(MPI_COMM_WORLD, &size); // size

	if (size != 12)
	{
		printf("Please run with 12 processes.\n");
		fflush(stdout);
		MPI_Abort(MPI_COMM_WORLD, 1);
	}

	dim[0] = 4;
	dim[1] = 3;
	period[0] = 1;
	period[0] = 1;
	reorder = 0;

	MPI_Cart_create(MPI_COMM_WORLD, 2, dim, period, reorder, &comm);
	// size - n - 1

	if (rank == 0)
	{
		MPI_Cart_coords(comm, 2, 2, coord); // n - 1
		printf("Process %d: has left neighbour with coordinates (%d, %d)\t", rank, coord[0], coord[1]);

		MPI_Cart_coords(comm, rank + 1, 2, coord);
		printf("Process %d: has right neighbour with coordinates (%d, %d)\n", rank, coord[0], coord[1]);
	}
	else if (rank == size - 1) {
		MPI_Cart_coords(comm, 9, 2, coord); // size - n - 1
		printf("Process %d: has right neighbour with coordinates (%d, %d)\t", rank, coord[0], coord[1]);

		MPI_Cart_coords(comm, rank - 1, 2, coord);
		printf("Process %d: has left neighbour with coordinates (%d, %d)\n", rank, coord[0], coord[1]);
	}
	else {
		MPI_Cart_coords(comm, rank - 1, 2, coord);
		printf("Process %d: has left neighbour with coordinates (%d, %d)\t", rank, coord[0], coord[1]);

		MPI_Cart_coords(comm, rank + 1, 2, coord);
		printf("Process %d: has right neighbour with coordinates (%d, %d)\n", rank, coord[0], coord[1]);
	}

	MPI_Finalize();

    return 0;
}

