#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char **argv) {
 
    //  int n_elements;

    // printf("Elementos a serem lidos:\n");
    // scanf("%i\n", &n_elements); 

    MPI_Init(&argc, &argv);

    int rank, size;
    //  double buffer[n_elements];
  
    FILE *infile;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

  // Input reading for process 0

    int n_elements;
    double *ptr;
    ptr = malloc(sizeof(double));
    
//  if (rank == 0) {

    infile = fopen("data", "r");
    /********* reading the number of elements in n_elements  ********/
    fscanf(infile,"%d\n", &n_elements);
     double buffer[n_elements];
    for(int i=0; i < n_elements; i++)
      buffer[i] = 0;

    /*** storing each element in buffer[i]   *****/
    for (int i=0; i < n_elements; ++i)
    {
        fscanf(infile,"%lf\n", &buffer[i]);
        printf("Lendo %f\n", *(buffer+i));
    }
//  }
    // 1- Broadcast the value n_elements to all processes
    MPI_Bcast(&n_elements, size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(&buffer, size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
  // Here we create the buffers for the non-root processes now that
  // we have n_elements
  if (rank == 1){
    int i, counter=1;
    for (i=0; i < n_elements; i++){
         if (buffer[i] > 0) {
            ptr = buffer + i;
            counter++;
            ptr = realloc(ptr, counter * sizeof(double));
        }       
    }
    MPI_Bcast(ptr, size, MPI_DOUBLE, rank, MPI_COMM_WORLD);
  } 
  // 2- Broadcast the buffer to every process
  //    NOTE : The type here should be MPI_DOUBLE not MPI_FLOAT !
  // [...]

    // 3- Compute the sum depending on the rank

    double sum = 0.0;
//    // [...]

        if (rank == 1){
            for (int i = 0; i < 2; i++)
                sum += ptr[i]; 
        }
//    if( rank == 0) {
//            double sum = 0.0;
//     /* do some work as process 0 */
//
//     for (int i = 0; i < n_elements; i++)
//        sum += buffer[i]; 
//    }
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
//  printf("Processo #%d - soma = %f\n", rank, sum);
  MPI_Finalize();
//  delete [] buffer;

  return 0;
}
