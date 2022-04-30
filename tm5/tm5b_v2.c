/* tm5b_v2.c - array searching example where each process is looking for a specific
   size_array and notifies the other processes when it finds it. Uses a non-blocking receive.
*/
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    int rank,size, n_elements_recieved;
    MPI_Status status;
    // MPI_Request request;
    int nvalues;
    
    int *array, *temp;
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
        // printf("Qual o valor que você está buscando? ");
        // fflush(stdout); // MPI: Força a execução da declaração printf
        // scanf("%d", &buscado);

        // Lê arquivo
        infile=fopen("data.txt","rt");
        
        fscanf(infile,"%d",&buscado);       // Número procurado
        fscanf(infile,"%d",&size_array);    // Máximo de elementos do array
        array = realloc(array, size_array * sizeof(int));
        printf("Lendo!\n");
        fflush(stdout);
        // Constroi array
        for(i = 0; i < size_array; ++i) {
            fscanf(infile,"%d",&array[i]);
        }
        printf("leitura finalizada\n");
        fflush(stdout);
    } 

    // Envia os dados para os processos
    nvalues = size_array / size ;   // elementos por processo
    // printf("\n\n%d %d\n", rank, array[0]);
    temp = realloc(temp, nvalues * sizeof(int));

    MPI_Scatter(array, nvalues, MPI_INT, temp, nvalues, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("4. Processor %d has data: ", rank);
        for (i=0; i<size; i++)
            printf("%d ", array[i]);
        printf("\n");
    }
    // printf("1. Processor %d has data %d\n", rank, *temp);

        // MPI_Barrier(MPI_COMM_WORLD);

        // MPI_Gather(temp, nvalues, MPI_INT, array, size_array, MPI_INT, 0, MPI_COMM_WORLD);
        // printf("2. Processor %d has data %d\n", rank, *temp);
        // MPI_Gather(temp, 1, MPI_INT, array, size_array, MPI_INT, 0, MPI_COMM_WORLD);
    
        free(temp);
        free(array);
        MPI_Finalize();
        return 0;
    //     // Verifica se mais de um processo está rodando
    //     if (size > 1) {
    //         for (i = 1; i < size - 1 ; i++){
    //             index = i * nvalues;
    //             MPI_Send(&nvalues, 1, MPI_INT, i, 123, MPI_COMM_WORLD);
    //             MPI_Send(&buscado, 1, MPI_INT, i, 123, MPI_COMM_WORLD);
    //             MPI_Send(&array[index], nvalues, MPI_INT, i, 123, MPI_COMM_WORLD);
    //         }
            
    //         // Adiciona elementos ao ultimo processo
    //         index = i * nvalues;
    //         int elements_left = size_array - index;
    //         MPI_Send(&elements_left, 1, MPI_INT, i, 123, MPI_COMM_WORLD);
    //         MPI_Send(&buscado, 1, MPI_INT, i, 123, MPI_COMM_WORLD);
    //         MPI_Send(&array[index], elements_left, MPI_INT, i, 123, MPI_COMM_WORLD);
    //     }

    //     int counter = 0;
    //     dummy = -1;
    //     for (i = 0; i < nvalues; i++){
    //         if (array[i] == buscado){
    //             dummy = i + rank * nvalues;
    //             n_elements_recieved = 0;
    //         }
    //         // printf("master %d counter %d process: values are %d\n", rank, counter++, array[i]);
    //     }
    //     MPI_Send(&dummy, 1, MPI_INT, 0, 123, MPI_COMM_WORLD);
    //     MPI_Recv(&dummy, 1, MPI_INT, source, 123, MPI_COMM_WORLD, &status);
    // } else {    // SLAVE
    //     MPI_Recv(&n_elements_recieved, 1, MPI_INT, 0, 123, MPI_COMM_WORLD, &status);
    //     MPI_Recv(&buscado, 1, MPI_INT, 0, 123, MPI_COMM_WORLD, &status);
    //     temp = realloc(temp, n_elements_recieved * sizeof(int));
    //     MPI_Recv(temp, n_elements_recieved * sizeof(int), MPI_INT, 0, 123, MPI_COMM_WORLD, &status);
    //     int counter = 0;
    //     dummy = -1;
    //     for (i = 0; i < n_elements_recieved - 1; i++){
    //         if (temp[i] == buscado){
    //             dummy = i + rank * n_elements_recieved;
    //             n_elements_recieved = 0;
    //         }
    //         // printf("master %d counter %d process: values are %d\n", rank, counter++, temp[i]);
    //     }
    //     free(temp);
    //     MPI_Send(&dummy, 1, MPI_INT, 0, 123, MPI_COMM_WORLD);
    // }
    // if (dummy != -1)
    //     printf("Elemento %d achado na posição %d da lista \n", buscado, dummy);
    // MPI_Finalize();
    // free(array);
}
