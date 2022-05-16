#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mpi.h"

#define buffer_count 10000

int main( argc, argv )
int argc;
char **argv;
{   
    int rank,  size;
    int buffer[buffer_count], recv_buffer[buffer_count];

    MPI_Request request;
    MPI_Status  status;
    int request_finished = 0;
    int ready;


    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);


    // Initialising buffer :
    for (int i=0; i < buffer_count; ++i)
      buffer[i] = (rank == 0 ? i*2 : 0);

    MPI_Barrier(MPI_COMM_WORLD);
    // Starting the chronometer
    double time = -MPI_Wtime(); // This command helps us measure time. We will see more about it later on !
    
    if (rank == 0) {
      sleep(3);

      // 1- Initialise the non-blocking send to process 1
      // [...]
      MPI_Isend(&buffer, buffer_count, MPI_INT, 1, 321, MPI_COMM_WORLD, &request); //non blocking send to destination process

      double time_left = 6000.0;
      while (time_left > 0.0) {
        usleep(1000); // We work for 1ms

        // 2- Test if the request is finished (only if not already finished)
        // [...]
        
        MPI_Test(&request, &ready, MPI_STATUS_IGNORE);

        // 1ms left to work
        time_left -= 1000.0;
      }

      // 3- If the request is not yet complete, wait here. 
      // [...]
      if (ready){
        printf("enviado!");
      } else {
        MPI_Wait(&request, MPI_STATUS_IGNORE);
      }

      // Modifying the buffer for second step
      for (int i=0; i < buffer_count; ++i)
        buffer[i] = -i;

      // 4- Prepare another request for process 1 with a different tag
      // [...]
      MPI_Isend(&buffer, buffer_count, MPI_INT, 1, 123, MPI_COMM_WORLD, &request); //non blocking send to destination process

      time_left = 3000.0;
      while (time_left > 0.0) {
        usleep(1000); // We work for 1ms

        // 5- Test if the request is finished (only if not already finished)
        // [...]
        MPI_Test(&request, &ready, MPI_STATUS_IGNORE);

        // 1ms left to work
        time_left -= 1000.0;
      }
      // 6- Wait for it to finish
      // [...]
      if (ready){
        printf("enviado!");
      } else {
        MPI_Wait(&request, MPI_STATUS_IGNORE);
      }
      
    }
    else {
      // Work for 5 seconds
      sleep(5);

      // 7- Initialise the non-blocking receive from process 0
      // [...]
      MPI_Irecv(recv_buffer, buffer_count, MPI_INT, 0, 321, MPI_COMM_WORLD,&request);

      // 8- Wait here for the request to be completed
      // [...]
      MPI_Wait(&request, MPI_STATUS_IGNORE);

      // print_buffer(recv_buffer);
//      printf("\n");
  //    for (int i=0; i <buffer_count; i++){
    //    printf("%d ", recv_buffer[i]);
      //}
      
      // Work for 3 seconds
      sleep(3);

      // 9- Initialise another non-blocking receive
      // [...]
      MPI_Irecv(recv_buffer, buffer_count, MPI_INT, 0, 123, MPI_COMM_WORLD,&request);
      
      // 10- Wait for it to be completed
      // [...]
      MPI_Wait(&request, MPI_STATUS_IGNORE);

      // print_buffer(buffer);
      //printf("\n");
      //for (int i=0; i <buffer_count; i++){
       // printf("%d ", recv_buffer[i]);
     // }
    }
    

    // Stopping the chronometer
    time += MPI_Wtime();

    // This line gives us the maximum time elapsed on each process.
    // We will see about reduction later on !
    double final_time;
    MPI_Reduce(&time, &final_time, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
    
    if (rank == 0)
      printf( "Total time for non-blocking scenario : %f seconds\n", final_time );

  //[....]
  MPI_Finalize();

} // END OF MAIN


// void print_buffer(int *buffer){
//   int size = sizeof(&buffer)/sizeof(int);
//   for (int i=0; i < size; i++){
//         printf("%d ", buffer[i]);
//   }
// }
