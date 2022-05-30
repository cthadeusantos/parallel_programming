#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define SIZE 800

void fill_matrix(int *matrix){
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            *((matrix + SIZE * i) + j) = rand() % 10;
        }
    }
}

void print_matrix(int *matrix){
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            printf("%d ", matrix[i*SIZE + j]);
        }
        printf("\n");
    }
    printf("\n");
}



int main(int argc, char *argv[]) {
    int A[SIZE][SIZE], B[SIZE][SIZE], C[SIZE][SIZE];

    int i, j,k, N;
    // N = atoi(argv[1]);
    fill_matrix(&A[0][0]);
    fill_matrix(&B[0][0]);
    fill_matrix(&C[0][0]);
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++){
            C[i][j] = 0.0;
            for (k = 0; k < SIZE; k++) {
                C[i][j] +=  A[i][k] * B[k][j];
            }    
        }
    }
    print_matrix(&C[0][0]);
}
