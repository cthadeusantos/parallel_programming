/*
 * You must install openMPI library
 *
 * Compile with:
 * mpicc simple1.c -o output
 *
 * Run using:
 * mpirun -n X output
 * or
 * mpirun -np X output
 *
 * where arg X is the processors' numbers.
 * if  the message "There are not enough slots available in the system to satisfy the X slots that were requested by the application" are returned, add --oversubscribe at mpirun arguments.
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mpi.h>

int main(int argc, char** argv)
{
	int meu_rank, np, origem, destino, tag=0;
	char msg[100];
	MPI_Status status;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &meu_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &np);

	if (meu_rank != 0){
		sprintf(msg, "Processo %d está vivo!", meu_rank);
		destino = 0;
		int tam = strlen (msg) + 1;
		MPI_Send(msg, tam, MPI_CHAR, destino, tag, MPI_COMM_WORLD);
	} else {
		for (origem = 1; origem < np; origem++){
			MPI_Recv(msg, 100, MPI_CHAR, origem, tag, MPI_COMM_WORLD, &status);
			printf("%s\n", msg);
		}
	}
	MPI_Finalize();	
}
