/*
 * You must install openMPI library
 *
 * Compile with:
 * mpicc hello_world.c -o output
 *
 * Run using:
 * mpirun -n X output
 * or
 * mpirun -np X output
 *
 * where arg X is the processors' numbers.
 * if  the message "There are not enough slots available in the system to satisfy the X slots that were requested by the application" are returned, add --oversubscribe at mpirun arguments.
 */

#include <stdio.h>
#include <mpi.h>

int main(argc , argv)
int argc;
char **argv;
{
	int rank, size;
	MPI_Init( &argc, &argv );
	MPI_Comm_size( MPI_COMM_WORLD, &size);
	MPI_Comm_rank( MPI_COMM_WORLD, &rank);
	printf("Hello world from process %d of %d\n", rank, size);
	MPI_Finalize();
	return 0;
}
