
CC = mpicc
CFLAGS = -Wall -ansi -pedantic -std=c99

mpi:
	INPUT=sieve_par_MPI
	OUTPUT = mpi
	LFLAGS = -o$(OUTPUT) -fopenmp -lm
	$(INPUT): $(INPUT).c
		$(CC) $(FLAGS) $(INPUT).c $(LFLAGS)

hib:
	INPUT = sieve_par_HIB
	OUTPUT = hibrido
	LFLAGS = -o$(OUTPUT) -fopenmp -lm
	$(INPUT): $(INPUT).c
		$(CC) $(FLAGS) $(INPUT).c $(LFLAGS)

clean:
	rm -f $(PROG) a.out *~ *# *.o