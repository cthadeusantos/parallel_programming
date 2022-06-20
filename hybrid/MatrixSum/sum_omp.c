#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void fill_matrix(int *matrix, int size){
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            *((matrix + size * i) + j) = rand() % 10;
        }
    }
}

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

    if (argc < 4){
        printf("USAGE: omp.out [row] [col] [num_threads]\n");
        exit(1);
    }

    
    int numthreads, rows, cols, nelements;

    rows = atoi(argv[1]);
    cols = atoi(argv[2]);
    nelements = rows * cols;
    numthreads = atoi(argv[3]);

    // printf("rows %i cols %i threads %i\n", rows, cols, numthreads);

    int *A = calloc(nelements, sizeof(int));
    int *B = calloc(nelements, sizeof(int));
    int *C = calloc(nelements, sizeof(int));
    double start; 
    double end; 
    
    for (int i=0; i < rows; i++){
        for (int j=0; j < cols; j++){
            int index = i * cols + j;
            // A[index] = rand() % 100;
            // B[index] = rand() % 100;
            A[index] = rows + i;
            B[index] = cols - j;
            C[index] = 0;
        }
    }

    start = omp_get_wtime();
    omp_set_num_threads(numthreads);
        #pragma omp parallel for
        for (int i=0; i < rows; i++){
            for (int j=0; j < cols; j++){
                int index = i * cols + j;
                C[index] = A[index] + B[index];
            }
        }
        #pragma omp critical
    end = omp_get_wtime();
    // print_matrix(C, rows, cols);
    free(A);
    free(B);
    free(C);
    printf("Tempo de processamento paralelo OMP: %lf\n", end - start);

}
