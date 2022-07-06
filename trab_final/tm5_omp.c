/* tm5_seq.c
Busca por um valor em um array sem paralelismo

Entrada de dados feita através de um arquivo
Primeira linha , valor a ser pesquisado
Segunda linha, Tamanho do array
Demais linhas (quantidade deve ser no mínimo o valor informado na segunda linha) valores do vetor

*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

int main(int argc, char* argv[]) {
    int rank,size, n_elements_recieved;
    int nvalues;
    int *array=NULL, *temp=NULL;
    float time1, time2, delta_time;
	int *vetor;
	int id=-1; // number of thread in use
	// Time before the loop began
	double start_time;
	// Time right now
	double current_time;
	// Elapsed time since beginning of loop
	double elapsed_time;

	/* first input parameter defines the number of threads */
    int nthreads = atoi(argv[1]);
    omp_set_num_threads(nthreads);
    array = malloc(sizeof(int));
    temp = malloc(sizeof(int));

    int i,j, buscado, size_array;
    FILE *infile;

    // Gera os dados

        // Lê arquivo
        infile=fopen("data.txt","rt");
        
        fscanf(infile,"%d",&buscado);       // Número procurado
        fscanf(infile,"%d",&size_array);    // Máximo de elementos do array
        array = realloc(array, (int)((size_array) * sizeof(int)));
        // Constroi array
        for(i = 0; i < size_array; ++i) {
            fscanf(infile,"%d",&array[i]);
        }
        fclose(infile);

        int found = 0;
        start_time = omp_get_wtime();
        #pragma omp parallel for schedule(auto) num_threads(nthreads) private(id,i) shared(size_array,array, found)
        for (i = 0; i < size_array; i++){
            if (array[i] == buscado){
                id = omp_get_thread_num();
                printf("Valor %d encontrado na posicao %d da thread %d\n", array[i], i, id);
                i = size_array+1;
                found = 1;
            }
            if (found)
                i = size_array+1;
        }
        // Get the new time
		current_time = omp_get_wtime();
		// Update the elapsed time
		elapsed_time = current_time - start_time;
        if (!found) {
            printf("Não encontrei o valor %d \n", buscado);
        } else {
            printf("Tempo decorrido na busca %lf \n", elapsed_time);
        }
    
        free(array);
        free(temp);
        return 0;
}
