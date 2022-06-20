#include <mpi.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

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
	int rank, size;
    if (argc < 3){
        printf("USAGE: sum_mpi2.out [row] [col]\n");
        exit(1);
    }

    double start; 
    double end; 

    MPI_Init(&argc, &argv); //to initial MPI with argument | ex. argument = 1, argc = 1, argv(vector) = "1"
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); //ID of processor
    MPI_Comm_size(MPI_COMM_WORLD, &size); //amount of processor
    int rows, cols, nelements, size_submatrix, size_last_submatrix, offset;
    int i, j, k, r, index;
    rows = atoi(argv[1]);
    cols = atoi(argv[2]);
    nelements = rows * cols;

	//Code that will execute inside process 0 or rank 0
    if (rank == 0){
        int *A = calloc(nelements, sizeof(int));
        int *B = calloc(nelements, sizeof(int));
        int *C = calloc(nelements, sizeof(int));

        for (i=0; i < rows; i++){
            for (j=0; j < cols; j++){
            int index = i * cols + j;
            // A[index] = rand() % 100;
            // B[index] = rand() % 100;
            A[index] = rows + i;
            B[index] = cols - j;
            C[index] = 0;
            }
        }
        size_submatrix = (int)rows / size;
        if (size_submatrix * size < rows)
            size_submatrix++;
        size_last_submatrix = rows - (size_submatrix * (size - 1));

        // Job begins for me, check the clock
        start = MPI_Wtime();

        //Addition in rank 0
        for(i = 0 ; i < size_submatrix ; i++)
            for(j = 0; j < cols; j++){
                index = i * rows + j;
                C[index] = A[index] + B[index];
            }

        if (size != 1){
            //send detail to all rank
            for (r = 1; r < size; r++)
            {
                MPI_Send(&cols, 1, MPI_INT, r, 1, MPI_COMM_WORLD);
                if (r == (size - 1))
                    MPI_Send(&size_last_submatrix, 1, MPI_INT, r, 2,MPI_COMM_WORLD);
                else
                    MPI_Send(&size_submatrix, 1, MPI_INT, r, 2,MPI_COMM_WORLD);
            }

            //send part LOOP
            for (r = 1; r < size; r++){ // Rank 
                // for(i = 0 ; i < size_submatrix ; i++){
                    offset = cols * size_submatrix * r;
                    int send_elements = size_submatrix * cols;
                    if (r == size - 1){
                        send_elements = size_last_submatrix * cols;
                    }
                    MPI_Send(&A[offset], send_elements, MPI_INT, r, 3, MPI_COMM_WORLD);
                    MPI_Send(&B[offset], send_elements, MPI_INT, r, 4, MPI_COMM_WORLD);
                // }
            }
        }

        //receive matrix C after other rank calcutate
        for (r = 1; r < size; ++r){
            int _rank;
            MPI_Recv(&_rank, 1, MPI_INT, r, 6, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            offset = cols * size_submatrix * _rank;
            int recv_elements = size_submatrix * cols;
            if (r == size - 1){
                recv_elements = size_last_submatrix * cols;
            }
            MPI_Recv(&C[offset], recv_elements, MPI_INT, r, 5, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }

        // Wait for the very last one to 
        end = MPI_Wtime();
        free(A);
        free(B);
        free(C);
        // printf("Calculei a soma das matrizes\n");
        printf("Tempo de processamento paralelo MPI: %lf\n", (end - start));
    }

    if (rank != 0) {

        MPI_Recv(&cols, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&size_submatrix, 1, MPI_INT, 0, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        nelements = size_submatrix * cols;
    
        int *A = calloc(nelements, sizeof(int));
        int *B = calloc(nelements, sizeof(int));
        int *C = calloc(nelements, sizeof(int));

        MPI_Recv(&A[0], nelements, MPI_INT, 0, 3, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&B[0], nelements, MPI_INT, 0, 4, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        
        for(i = 0 ; i < size_submatrix ; i++){
            for(j = 0; j < cols; j++){
                index = i * cols + j;
                C[index] = A[index] + B[index];
            }
        }

        MPI_Send(&rank, 1, MPI_INT, 0, 6, MPI_COMM_WORLD);
        MPI_Send(&C[0], nelements, MPI_INT, 0, 5, MPI_COMM_WORLD);
        free(A);
        free(B);
        free(C);
    }


    MPI_Finalize();
    return 0;
	
}