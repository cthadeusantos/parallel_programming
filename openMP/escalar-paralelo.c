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

    omp_set_num_threads(num_threads);

    for (i=0; i<n; i++){
        a[i] = i * 0.5;
        b[i] = i * 2.0;
    }
    float tik = clock();
    float tok;
    #pragma omp parallel
    {
        sum = 0;

        for (i=1; i<n; i++){
            sum = sum + a[i]*b[i];
        }
    }
    #pragma omp barrier
    
    
    tok = clock();
    printf("Tempo de execução: %f\n", (tok - tik)/CLOCKS_PER_SEC);

    printf ("sum = %f\n", sum);
}