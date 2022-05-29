/*
Compile usando -lm por causa de sqrt
gcc openMP4.c -fopenmp -o output -lm

Paralelizando o loop com PARALLEL FOR
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <omp.h>

void inicializa(int **v, int size) {
  (*v) = (int *) malloc(sizeof(int)*size);
  for (int i = 0; i < size; i++) 
    (*v)[i] = rand() % 10000;
}

float square(int x){
  int k = 0;
  while(k < 5000) k++;  // busy waiting
  return sqrt(x);  
}

int main(int argc, char **argv) {
	FILE *out_file = fopen("openMPv5.txt", "w"); // write only
	// test for files not existing. 
	if (out_file == NULL) 
	{   
		printf("Error! Could not open file\n"); 
		exit(-1); // must include stdlib.h 
	}
	srand(time(NULL));
	int *vetor;
	int id; // number of thread in use

	/* first input parameter defines the vector size */
	int size = atoi(argv[1]);
	inicializa(&vetor, size);

	/* second input parameter defines the number of threads */
    int nthreads = atoi(argv[2]);
    omp_set_num_threads(nthreads);

		/* third input parameter defines the chunck number */
    int chunck_size = atoi(argv[3]);
    
	#pragma omp parallel for schedule (dynamic, chunck_size) num_threads(nthreads) private(id) shared(size, vetor)
	for(int i = 0; i < size; i++){
		id = omp_get_thread_num();
		int aux = vetor[i];
		vetor[i] = square(vetor[i]);
		fprintf(out_file, "Thread %i indice %i valor %i raiz aproximada %i\n", id, i, aux, vetor[i]); // write to file
	}
	// todas as threads processadas

	#pragma omp barrier
	printf("Finalização da rotina!\n");
	
	
}
