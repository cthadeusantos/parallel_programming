// Exercite a operação reduce através do programa que calcula o produto escalar. Complete as lacunas

#include <stdio.h>
#include <mpi.h>
#include <math.h>


int main(int argc, char **argv) {
   // MPI initialization 
   //[....]
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);


    // The initial values, u_i = i^2; v_i = log(i+1)
    float u_i = rank*rank;
    float v_i = log(rank+1.0);

    // Each process computes its intermediate value
    //[....]
    float temp = u_i * v_i;

    // Reducing on process 0 :
    //    [....]
    float dot_product;

    MPI_Reduce(&temp, &dot_product, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);

// Validating the result

   if (rank == 0) {        printf ("The reduced value is %f on rank 0\n", dot_product );

       // Checking the result
      float validation = 0.0f;
      for (int i=0; i < size; ++i)
        validation += i*i * log(i+1.0f);

       printf ( "Validation gives the value : %f\n ", validation );
  }else {
        // print tmp and result in each other process 
        //    [....]
        printf("Intermediate values: rank %d product %f \n", rank, temp);
  }

  
  MPI_Finalize();
  
  return 0;
}
