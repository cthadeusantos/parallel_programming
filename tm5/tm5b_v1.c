/* tm5a_v1.c
Busca por um valor em um array utilizando MPI_BCAST e MPI_SCATTER

Através do terminal, deve ser fornecido o valor a ser
pesquisado e o número de elementos a ser criado em um array
aleatório
*/
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    int rank,size, n_elements_recieved;
    MPI_Status status;
    // MPI_Request request;

    int nvalues;
    int *array=NULL, *temp=NULL;

    float time1, time2, delta_time;

    array = malloc(sizeof(int));
    temp = malloc(sizeof(int));

    int i,j, buscado, size_array;
    FILE *infile;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    // Gera os dados
    if (rank == 0) {    // MASTER

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
    }
        
        time1 = MPI_Wtime();
        MPI_Bcast(&buscado, 1, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Bcast(&size_array, 1, MPI_INT, 0, MPI_COMM_WORLD);
        nvalues = (int) size_array / size ;   // elementos por processo
        MPI_Bcast(&nvalues, 1, MPI_INT, 0, MPI_COMM_WORLD);
        temp = realloc(temp, nvalues * sizeof(int));
        MPI_Scatter(array, nvalues, MPI_INT, temp, nvalues, MPI_INT, 0, MPI_COMM_WORLD);
        
        for (i = 0; i < nvalues; i++){
            if (temp[i] == buscado){
                printf("Valor encontrado %d no rank %d\n", temp[i], rank);
                nvalues = 0;
            }
        }
        time2 = MPI_Wtime();
        delta_time = time2 - time1;
        if (nvalues == 0)
            printf("Variação de tempo %f no rank %d.\n", delta_time, rank);
        free(array);
        free(temp);

        MPI_Finalize();
        return 0;
}
