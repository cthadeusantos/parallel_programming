#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <omp.h>

#define SIZE 1000

void fill_matrix(int *matrix, int size){
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            *((matrix + size * i) + j) = rand() % 10;
        }
    }
}

void print_matrix(int *matrix, int size){
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            printf("%d ", matrix[i*size + j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    //int A[SIZE][SIZE], B[SIZE][SIZE], C[SIZE][SIZE];
    if (argc != 3){
        printf("Usage: output [size] [threads]\n");
        exit(1);
    }
    int i, j,k, num_threads;
    int size = atoi(argv[1]);
    num_threads = atoi(argv[2]);

    int A[size][size], B[size][size], C[size][size];

    printf("Preenchendo as matrizes\n");
    fill_matrix(&A[0][0], size);
    fill_matrix(&B[0][0], size);
    //fill_matrix(&C[0][0], size);
    printf("Multiplicando as matrizes\n");
    omp_set_num_threads(num_threads);
    float tik = clock();
    float tok;
    #pragma omp parallel private(k) shared(C)
    {
        #pragma omp for
        for (i = 0; i < size; i++) {
            for (j = 0; j < size; j++){
                C[i][j] = 0.0;
                for (k = 0; k < size; k++) {
                    C[i][j] +=  A[i][k] * B[k][j];
                }    
            }
        }
    }
    #pragma omp barrier
    tok = clock();
    printf("Tempo de multiplicação das matrizes: %f\n", (tok - tik)/CLOCKS_PER_SEC);
    //print_matrix(&C[0][0], size);
}
