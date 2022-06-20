#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_matrix(int *matrix, int rows, int cols){
    int nelements = rows * cols;
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            int index = cols * i + j;
            printf("%i ", *(matrix + index));
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]){

    if (argc < 3){
        printf("USAGE: sum_mpi.out [row] [col]\n");
        exit(1);
    }
    
    int rows, cols;

    // numthreads = atoi(argv[1]);
    rows = atoi(argv[1]);
    cols = atoi(argv[2]);

    int *A = calloc(rows * cols, sizeof(int));
    int *B = calloc(rows * cols, sizeof(int));
    int *C = calloc(rows * cols, sizeof(int));
    double start; 
    double end; 
    
    for (int i=0; i < rows; i++){
        for (int j=0; j < cols; j++){
            int index = i * cols + j;
            A[index] = rows + i;
            B[index] = cols - j;
            C[index] = 0;
        }
    }

    start = clock();
        for (int i=0; i < rows; i++){
            for (int j=0; j < cols; j++){
                int index = i * cols + j;
                C[index] = A[index] + B[index];
            }
        }
    end = clock();
    // print_matrix(C, rows, cols);
    free(A);
    free(B);
    free(C);
    printf("Tempo de processamento sequencial: %lf\n", (double)(end - start)/ CLOCKS_PER_SEC);

}
