#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char **argv) {
 
  int n_elements;
  printf("Elementos a serem lidos:\n");
  scanf("%i\n", &n_elements); 
    
  MPI_Init(&argc, &argv);

  int rank, size;
  
  FILE *infile;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  // Input reading for process 0

  double *buffer[n_elements];
  
  if (rank == 0) {
    /********* reading the number of elements in n_elements  ********/
//    buffer[n_elements] = {0};
    infile = fopen("data", "r");
    for (int i=0; i < n_elements; ++i)
    {
        fscanf(infile,"%lf\n", &buffer[i]);
        printf("%lf\n", *(buffer+i));
    }
 
      /*** storing each element in buffer[i]   *****/
  }

  // 1- Broadcast the value n_elements to all processes
  // [...]


  // Here we create the buffers for the non-root processes now that
  // we have n_elements
//  if (rank != 0)
//    buffer = new double[n_elements];

  // 2- Broadcast the buffer to every process
  //    NOTE : The type here should be MPI_DOUBLE not MPI_FLOAT !
  // [...]
  

  // 3- Compute the sum depending on the rank
  double sum = 0.0;
  // [...]

  
  // Printing the result and terminating the program
  // Precision is set high for the validation process, please do not modify this.
  // [....] //
  
  MPI_Finalize();
//  delete [] buffer;

  return 0;
}
