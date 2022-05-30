#include <omp.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv){
    int size = atoi(argv[1]);
    omp_set_num_threads(size);
    #pragma omp parallel num_threads(size)
    {
        int np = omp_get_num_threads();
        int iam = omp_get_thread_num();
        printf("Hello from thread %d (total %d)\n", iam, np);
    }
}
