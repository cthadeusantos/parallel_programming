/*
 * You must install openMPI library
 *
 * Compile with:
 * mpicc iterativo1.c -o output
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
#include <stdlib.h>
#include <mpi.h>

int main (argc, argv)
int argc;
char **argv;
{
    int rank, value, size;
    MPI_Status status;
    MPI_Init (&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    printf("Hello world from process %d of %d\n", rank, size);
    do {
        /* mestre */
        if (rank == 0){
            scanf("Entre um valor: %d", &value);
            MPI_Send(&value, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
        } else { /*trabalhores */
            MPI_Recv( &value, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, &status);
            if (rank < size -1)
                MPI_Send(&value, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
        }
        printf("Process %d get %d\n", rank, value);

    } while (value > 0);

}
