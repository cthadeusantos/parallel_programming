#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <mpi.h>

int main(int argc, char **argv) {

    //  int n_elements;

    // printf("Elementos a serem lidos:\n");
    // scanf("%i\n", &n_elements);

    MPI_Init(&argc, &argv);
    MPI_Status status;

    int rank, size;
    int n_elements;
    double *buffer;
    buffer = malloc(sizeof(double));

    FILE *infile;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    // MPI_Barrier(MPI_COMM_WORLD);



  // Input reading for process 0
    if (rank == 0) {
      infile = fopen("data", "r");
      /********* reading the number of elements in n_elements  ********/
      fscanf(infile,"%d\n", &n_elements);
      MPI_Bcast(&n_elements, 1, MPI_INT, 0, MPI_COMM_WORLD);

      buffer = realloc(buffer, n_elements * sizeof(double));
      for(int i=0; i < n_elements; i++)
        *(buffer+i) = 0;

      /*** storing each element in buffer[i]   *****/
      for (int i=0; i < n_elements; ++i)
          fscanf(infile,"%lf\n", &buffer[i]);
      // MPI_Bcast(&buffer, n_elements * sizeof(double), MPI_DOUBLE, 0, MPI_COMM_WORLD);
    }
    
    // 1- Broadcast the value n_elements to all processes
        // MPI_Barrier(MPI_COMM_WORLD);
    MPI_Bcast(&n_elements, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&buffer, n_elements * sizeof(double), MPI_DOUBLE, 0, MPI_COMM_WORLD);


  // Here we create the buffers for the non-root processes now that
  // we have n_elements

  // 2- Broadcast the buffer to every process
  //    NOTE : The type here should be MPI_DOUBLE not MPI_FLOAT !
  // [...]
      if (rank == 0){
        double *ptr;
        int i, counter = 0;
        ptr = malloc(sizeof(double));

        printf("Rank %d : %d \n", rank, n_elements);
        for (i=0; i < n_elements; i++){
              counter++;
              ptr = realloc(ptr, counter * sizeof(double));
              *(ptr + i) = *(buffer + i);
        }
        // MPI_Barrier(MPI_COMM_WORLD);
        MPI_Bcast(&counter, 1, MPI_INT, rank, MPI_COMM_WORLD);
        MPI_Bcast(&ptr, counter * sizeof(double), MPI_DOUBLE, rank, MPI_COMM_WORLD);
        free(ptr);

    }
    if (rank == 1){
        double *ptr;
        int i, counter = 0;
        ptr = malloc(sizeof(double));
        printf("Rank %d : %d \n", rank, n_elements);
        MPI_Recv(&buffer, n_elements * sizeof(double), MPI_DOUBLE, 0, MPI_ANY_SOURCE, MPI_COMM_WORLD, &status);
        for (i=0; i < n_elements; i++){
            if (*(buffer + i) > 0) {
              counter++;
              ptr = realloc(ptr, counter * sizeof(double));
              *(ptr + i) = *(buffer + i);
            }
        }

        // MPI_Barrier(MPI_COMM_WORLD);
        MPI_Bcast(&counter, 1, MPI_INT, rank, MPI_COMM_WORLD);
        MPI_Bcast(&ptr, counter * sizeof(double), MPI_DOUBLE, rank, MPI_COMM_WORLD);
        free(ptr);
    }
    // if (rank == 2) {
    //   // MPI_Barrier(MPI_COMM_WORLD);
    //     double *ptr;
    //     int i, counter = 0, number;
    //     ptr = malloc(counter * sizeof(double));
    //     printf("Dentro processo %d \n",  rank);
    //     for (i=0; i < n_elements; i++){
    //       if (buffer[i] < 0) {
    //         counter++;
    //         ptr = realloc(ptr, counter * sizeof(double));
    //         ptr[i]= buffer[i];
    //     }
    //   }
    //   // MPI_Barrier(MPI_COMM_WORLD);
    //   MPI_Bcast(&counter, 1, MPI_INT, rank, MPI_COMM_WORLD);
    //   MPI_Bcast(&ptr, counter * sizeof(double), MPI_DOUBLE, rank, MPI_COMM_WORLD);
    //   free(ptr);
    // }

    // 3- Compute the sum depending on the rank

   double sum = 0.0;
////    // [...]
//
      //  if (rank == 1){
      //      for (int i = 0; i < 2; i++)
      //          sum += ptr[i];
      //  }
   if( rank == 0) {
      double sum = 0.0;
      printf("------%d\n", n_elements);
    /* do some work as process 0 */
      for (int i = 0; i < n_elements; i++)
        sum += buffer[i];
      // printf("------%f\n", sum);
   }
//    else if( my_id == 1 ) {
//
//     /* do some work as process 1 */
//    }
//    else if( my_id == 2 ) {
//
//     /* do some work as process 2 */
//    }


  // Printing the result and terminating the program
  // Precision is set high for the validation process, please do not modify this.
  // [....] //
  printf("Processo #%d - soma = %f\n", rank, sum);

  MPI_Finalize();
  free(buffer);
//  delete [] buffer;

  return 0;
}
