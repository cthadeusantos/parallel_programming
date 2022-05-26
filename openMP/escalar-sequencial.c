#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char* argv[])
{
    if (argc != 2){
        printf("Usage: output [size]\n");
        exit(1);
    }
    int n = atoi(argv[1]);
    double sum;
    double a[n], b[n];
    int i;
    for (i=0; i<n; i++){
        a[i] = i * 0.5;
        b[i] = i * 2.0;
    }
    sum = 0;
    float tik = clock();
    float tok;
    for (i=1; i<n; i++){
       sum = sum + a[i]*b[i];
    }

    tok = clock();
    printf("Tempo de execução: %f\n", (tok - tik)/CLOCKS_PER_SEC);
    printf ("sum = %f\n", sum);
}