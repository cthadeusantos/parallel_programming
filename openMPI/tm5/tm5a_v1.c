/* tm5a_v1.c
Busca por um valor em um array utilizando MPI_SEND e MPI_RECV

Através do terminal, deve ser fornecido o valor a ser
pesquisado e o número de elementos a ser criado em um array
aleatório

INSTRUCAO PARA OSX
Para evitar a msg:
A system call failed during shared memory initialization that should
not have.  It is likely that your MPI job will now either abort or
experience performance degradation.

digite export TMPDIR=/tmp no seu terminal

*/
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    int rank,size, n_elements_recieved, source;
    MPI_Status status;
    // MPI_Request request;
    int nvalues;
    float time1, time2, delta_time;

    int *array, *temp;
    array = malloc(sizeof(int));
    temp = malloc(sizeof(int));

    int i,j,dummy, buscado, size_array;
    FILE *infile;

    system("clear");

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    if (rank ==0){
        // Solicita numero a ser buscado
        printf("Qual o valor que você está buscando? ");
        fflush(stdout); // MPI: Força a execução da declaração printf
        scanf("%d", &buscado);

        printf("Quantidade de elementos no array: ");
        fflush(stdout); // MPI: Força a execução da declaração printf
        scanf("%d", &size_array);
        
        // Cria o array de forma aleatoria
        array = realloc(array, size_array * sizeof(int));
        for (i = 0; i < size_array; i++){
            array[i] = rand() % size_array;
        }
        time1 = MPI_Wtime();
    }

    
    if (rank == 0) {    // MASTER
        nvalues = size_array / size ;   // elementos por processo 
        int index;
        // Verifica se mais de um processo está rodando
        if (size > 1) {
            for (i = 1; i < size - 1 ; i++){
                index = i * nvalues;
                MPI_Send(&nvalues, 1, MPI_INT, i, 123, MPI_COMM_WORLD);
                MPI_Send(&buscado, 1, MPI_INT, i, 123, MPI_COMM_WORLD);
                MPI_Send(&array[index], nvalues, MPI_INT, i, 123, MPI_COMM_WORLD);
            }
            
            // printf("INDICE %d \n", i);
            // Adiciona elementos ao ultimo processo
            index = i * nvalues;
            int elements_left = size_array - index;
            MPI_Send(&elements_left, 1, MPI_INT, i, 123, MPI_COMM_WORLD);
            MPI_Send(&buscado, 1, MPI_INT, i, 123, MPI_COMM_WORLD);
            MPI_Send(&array[index], elements_left, MPI_INT, i, 123, MPI_COMM_WORLD);
        }

        int counter = 0;
        dummy = -1;
        for (i = 0; i < nvalues; i++){
            if (array[i] == buscado){
                dummy = i + rank * nvalues;
                n_elements_recieved = 0;
            }
        }
        MPI_Send(&dummy, 1, MPI_INT, 0, 123, MPI_COMM_WORLD);
        MPI_Recv(&dummy, 1, MPI_INT, 0, 123, MPI_COMM_WORLD, &status);
    } else {    // SLAVE
        MPI_Recv(&n_elements_recieved, 1, MPI_INT, 0, 123, MPI_COMM_WORLD, &status);
        MPI_Recv(&buscado, 1, MPI_INT, 0, 123, MPI_COMM_WORLD, &status);
        temp = realloc(temp, n_elements_recieved * sizeof(int));
        MPI_Recv(temp, n_elements_recieved * sizeof(int), MPI_INT, 0, 123, MPI_COMM_WORLD, &status);
        int counter = 0;
        dummy = -1;
        for (i = 0; i < n_elements_recieved - 1; i++){
            if (temp[i] == buscado){
                dummy = i + rank * n_elements_recieved;
                n_elements_recieved = 0;
            }
        }
        MPI_Send(&dummy, 1, MPI_INT, 0, 123, MPI_COMM_WORLD);
    }
    if (dummy != -1)
        printf("Elemento %d achado na posição %d da lista \n", buscado, dummy);

    MPI_Barrier(MPI_COMM_WORLD);
    if (rank == 0) {
        time2 = MPI_Wtime();
        delta_time = time2 - time1;
        printf("Variação de tempo %f.\n", delta_time);
    }
    free(temp);
    free(array);
    MPI_Finalize();

}
