#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main (argc, argv)
int argc;
char **argv;
{
	int rank, value, size;
	int origem, destino, tag= 0;
	char msg[100];
	MPI_Status Status;
	MPI_Init( &argc, &argv);
	MPI_Comm_rank( MPI_COMM_WORLD, &rank);
	MPI_Comm_size( MPI_COMM_WORLD, &size);
	do {
		if (rank == 0) {
			origem = 0;
			destino = origem + 1;
			scanf("Entre um valor %d", &value);
			sprintf(msg, "%d", value);
			MPI_Send(msg, 100, MPI_CHAR, destino, tag, MPI_COMM_WORLD);
			printf("Processo %d valor %d size %d mensagem %s\n", rank, value, size,msg);
		} else {
			MPI_Recv(msg, 100, MPI_CHAR, origem, tag, MPI_COMM_WORLD, &Status);
			destino = origem + 1;
			MPI_Send(msg, 100, MPI_CHAR, destino, tag, MPI_COMM_WORLD);
			printf("Processo %d destino %d valor %d size %d mensagem %s\n", origem, destino, value, size, msg);
		}
	} while (value>0);
	MPI_Finalize();
	return 0;
}

