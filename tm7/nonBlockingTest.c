#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mpi.h"

#define buffer_count 100

int main( argc, argv )
int argc;
char **argv;
{   
    int rank,  size;

    MPI_Request request;
    MPI_Status  status;
    int request_finished = 0;

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
            MPI_Isend(&buffer, count, MPI_INT, destination, tag, MPI_COMM_WORLD, &request); //non blocking send to destination process

      double time_left = 6000.0;
      while (time_left > 0.0) {
        usleep(1000); // We work for 1ms

        // 2- Test if the request is finished (only if not already finished)
        // [...]
        
        // 1ms left to work
        time_left -= 1000.0;
      }

      // 3- If the request is not yet complete, wait here. 
      // [...]

      // Modifying the buffer for second step
      for (int i=0; i < buffer_count; ++i)
        buffer[i] = -i;

      // 4- Prepare another request for process 1 with a different tag
      // [...]
      
      time_left = 3000.0;
      while (time_left > 0.0) {
        usleep(1000); // We work for 1ms

        // 5- Test if the request is finished (only if not already finished)
        // [...]

        // 1ms left to work
        time_left -= 1000.0;
      }
      // 6- Wait for it to finish
      // [...]
      
    }
    else {
      // Work for 5 seconds
      sleep(5);

      // 7- Initialise the non-blocking receive from process 0
      // [...]

      // 8- Wait here for the request to be completed
      // [...]

      print_buffer();
      
      // Work for 3 seconds
      sleep(3);

      // 9- Initialise another non-blocking receive
      // [...]
      
      // 10- Wait for it to be completed
      // [...]

      print_buffer();
    }
    

    // Stopping the chronometer
    time += MPI_Wtime();

    // This line gives us the maximum time elapsed on each process.
    // We will see about reduction later on !
    double final_time;
    MPI_Reduce(&time, &final_time, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
    
    if (rank == 0)
      printf( "Total time for non-blocking scenario : %f seconds\n", final_time );

  [....]

} // END OF MAIN