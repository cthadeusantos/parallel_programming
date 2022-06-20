clear
count=5
printf "PROCESSAMENTO SEQUENCIAL\n"
for i in $(seq $count); do
    ./sequencial.out 12500 12500
done

printf "PROCESSAMENTO PARALELO OMP\n"
for i in $(seq $count); do
    ./omp.out 12500 12500 2
done

printf "PROCESSAMENTO PARALELO MPI\n"
for i in $(seq $count); do
    mpirun -np 2 ./mpi_sum.out 12500 12500
done

printf "PROCESSAMENTO PARALELO HIBRIDO(OMP+MPI)\n"
for i in $(seq $count); do
    mpirun -np 2 ./hibrida.out 12500 12500
done

