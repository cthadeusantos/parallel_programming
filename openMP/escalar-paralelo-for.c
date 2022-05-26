/*
existe um bug pois está somando 46568 a mais do que a soma original
conseguida com escalar-paralelo e escalar-sequencial
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <omp.h>


int main(int argc, char* argv[])
{
    if (argc != 3){
        printf("Usage: output [size] [threads]\n");
        exit(1);
    }
    int n = atoi(argv[1]);
    int num_threads = atoi(argv[2]);
    double sum;
    double a[n], b[n];
    int i;

    double privsum = 0;

    omp_set_num_threads(num_threads);

    for (i=0; i<n; i++){
        a[i] = i * 0.5;
        b[i] = i * 2.0;
    }
    float tik = clock();
    float tok;

    #pragma omp parallel private(i) shared(sum, a, b, privsum)
    {
        #pragma omp for
        for (i=0; i<n; i++){
            privsum += (a[i]*b[i]);
        }
        #pragma omp critical
        {
            sum += privsum;
        }
    }
    
    tok = clock();
    printf("Tempo de execução: %f\n", (tok - tik)/CLOCKS_PER_SEC);

    printf ("sum = %f\n", sum);
}