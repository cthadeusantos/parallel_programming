clear
count=5
for i in $(seq $count); do
    ./seq_linux
done

for i in $(seq $count); do
    ./omp_linux 1
done

for i in $(seq $count); do
    mpirun -np 1 ./mpi_scatter.out
done

for i in $(seq $count); do
    mpirun -np 1 ./mpi_send.out
done