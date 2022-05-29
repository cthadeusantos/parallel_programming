/*
Compile usando -lm por causa de sqrt
gcc openMP4v1b.c -fopenmp -o output -lm

SEM O USO DE PARALELL FOR
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
	FILE *out_file = fopen("openMPv1b.txt", "w"); // write only
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
    

	// Define o tamanho do vetor
	int size_partition = int(size/nthreads) + 1;
	int last_partition = size_partition - 1;
	int index = 0;

	// Ao dividir o vetor, a última partição pode variar de acordo
	// com o a razao do tamanho do vetor pelo numero de threads 
	if (id=nthreads){
		size_partition = last_partition;
	}

	#pragma omp parallel num_threads(nthreads) private(id)
	{
		id = omp_get_thread_num();
		int aux;
		// cada partição do vetor recebe a raiz quadrada
		for(int i = 0; i < size_partition; i++){
			index = i + (id - 1) * nthreads;
			aux = vetor[index];
			vetor[index] = square(vetor[index]);
			fprintf(out_file, "Thread %i indice %i valor %d raiz %d\n", id, index, aux, vetor[index]); // write to file
		}
		//#pragma omp barrier
		printf("Apenas para controle, Thread %i\n", id);
	}
	#pragma omp barrier
	printf("Finalização da rotina!\n");
	
	
}
