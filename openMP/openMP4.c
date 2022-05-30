/*
Compile usando -lm por causa de sqrt
gcc openMP4.c -fopenmp -o output -lm
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
	srand(time(NULL));
	int *vetor;
	/* first input parameter defines the vector size */
	int size = atoi(argv[1]);
	inicializa(&vetor, size);

	for(int i = 0; i < size; i++){
			vetor[i] = square(vetor[i]);
	} 
}
