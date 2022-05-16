#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv){
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_COMM_rank(MPI_COMM_WORLD, &rank);
    MPI_COMM_size(MPI_COMM_WORLD, &size);
    
    // Initialising the data
    int buffer[5];
    if (rank==0) {
        // Storing some values in the buffer
        for (int i = 0; i < 5; i++)
            buffer[i] = i * i;
        for (int id_dest=1; id_dest < size; ++id_dest)
            MPI_Send(buffer, 5, MPI_INT, id_dest, 0, MPI_COMM_world);
    else {
        MPI_Recv(buffer, 5, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }   
    
    printf("Process #%d - Buffer = ", rank);
    for (int i=0; i < 5; i++)
        printf(" %d = ", buffer[i]);
    print("\n");
    MPI_Finalize();
}
