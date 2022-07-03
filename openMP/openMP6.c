#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <omp.h>

float f(int x, int IT){
  int k = x;
  while(k < IT) k++;  
  return (k);  
}

float g(int x, int IT){
  int res = x;
  for (int k = 0; k < IT; k++);  
       return (res);  
}

int main(int argc, char **argv) {

    if (argc < 1){
        printf("Usage: mp6 [num_threads]");
        exit(1);
    }

    /* first input parameter defines the number of threads */
    int nthreads = atoi(argv[1]);
    omp_set_num_threads(nthreads);

   int iter = atoi(argv[1]);
   
     float result = f(2, iter) + g(2, iter);
     
   return 0;
}