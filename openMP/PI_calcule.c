#include <omp.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

static long num_steps = 100000;    
double step;
#define  NUM_THREADS 8
int main ()
{
     double    pi;    
     step = 1.0/(double) num_steps;
     omp_set_num_threads(NUM_THREADS);
     float tik = clock();
     float tok;
     #pragma omp parallel 
        {
            int i, id, nthrds; 
            double x, sum;

            id = omp_get_thread_num();
            nthrds = omp_get_num_threads();  
            for (i=id, sum=0.0;  i< num_steps;  i=i+nthrds){  
                  x = (i+0.5)*step;
                  sum += 4.0/(1.0+x*x);
            }  
          #pragma omp critical
          tok = clock();
          pi += sum * step;
        }
          printf("PI calculado é igual a %f step %f\n", tok - tik, pi);


}
