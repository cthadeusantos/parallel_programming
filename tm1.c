#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mpi.h"

int main(argc, argv)
int argc;
char **argv;
{
    int rank, size, origem, destino, tag, np;
    char msg[100];
    MPI_Status status;
    MPI_Init( &argc, &argv );
    if ((size % 2)!=0){
        printf("O numero de processos precisa ser par!");
        MPI_Finalize();
        exit(1);
    }
    MPI_Comm_size( MPI_COMM_WORLD, &np );
    MPI_Comm_rank( MPI_COMM_WORLD, &rank );
    printf("Iniciando processo %d\n", rank);


    if (rank != 0) {
        // if (rank < size/2) {
        //     destino = origem + rank;
        // } else {
        //     destino = origem - rank;
        // };
        destino = origem + 1;
        int tam = strlen (msg)+1;
        MPI_Send(msg, tam, MPI_CHAR, destino, tag, MPI_COMM_WORLD);
        printf("Tarefa %d enviou seu id para %d\n", origem, destino);
        MPI_Recv(msg, 100, MPI_CHAR, destino, tag, MPI_COMM_WORLD, &status);

    } else { // if (rank == 0)
        for (origem = 1; origem < np; origem++){
            MPI_Send(msg, 100, MPI_CHAR, origem, tag, MPI_COMM_WORLD);
            MPI_Recv(msg, 100, MPI_CHAR, origem, tag, MPI_COMM_WORLD, &status);
            printf("Mensagem %s\n", msg);
        }
    }
    MPI_Finalize();
}

