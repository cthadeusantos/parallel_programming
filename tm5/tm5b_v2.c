/* tm5b_v2.c
Busca por um valor em um array utilizando MPI_BCAST e MPI_SCATTER

Entrada de dados feita através de um arquivo
Primeira linha , valor a ser pesquisado
Segunda linha, Tamanho do array
Demais linhas (quantidade deve ser no mínimo o valor informado na segunda linha) valores do vetor

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
        // temp1 = malloc(sizeof(int));

    int i,j, buscado, size_array;
    FILE *infile;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    // Gera os dados
    if (rank == 0) {    // MASTER

        // Lê arquivo
        infile=fopen("data.txt","rt");
        
        fscanf(infile,"%d",&buscado);       // Número procurado
        fscanf(infile,"%d",&size_array);    // Máximo de elementos do array
        array = realloc(array, (int)((size_array) * sizeof(int)));
        fflush(stdout);
        // Constroi array
        for(i = 0; i < size_array; ++i) {
            fscanf(infile,"%d",&array[i]);
        }
        fflush(stdout);
    }
        MPI_Barrier(MPI_COMM_WORLD);

        if (rank == 0)
            time1 = MPI_Wtime(); // Inicializa a contagem

        MPI_Bcast(&buscado, 1, MPI_INT, 0, MPI_COMM_WORLD); // Informa o valor procurado
        MPI_Bcast(&size_array, 1, MPI_INT, 0, MPI_COMM_WORLD);  // Informa o tamanho do array
        
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

        MPI_Barrier(MPI_COMM_WORLD);
        if (rank ==0){
            time2 = MPI_Wtime();
            delta_time = time2 - time1;
            printf("Variação de tempo %f\n", delta_time);
        }
    
        free(array);
        free(temp);

        MPI_Finalize();
        return 0;
}
