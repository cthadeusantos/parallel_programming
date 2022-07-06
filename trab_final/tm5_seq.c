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

int main(int argc, char* argv[]) {
    int rank,size, n_elements_recieved;
    int nvalues;
    int *array=NULL, *temp=NULL;
    float time1, time2, delta_time;
	int *vetor;

	// Time before the loop began
	double start_time;
	// Time right now
	double current_time;
	// Elapsed time since beginning of loop
	double elapsed_time;

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
        start_time = clock();
        for (i = 0; i < size_array; i++){
            if (array[i] == buscado){
                printf("Valor %d encontrado na posicao %d\n", array[i], i);
                i = size_array+1;
                found = 1;
            }
        }
        current_time = clock();
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
