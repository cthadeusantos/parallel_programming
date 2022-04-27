#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {

    FILE *infile;

  // Input reading for process 0

    int n_elements;
    double *buffer;
    buffer = malloc(sizeof(double));

    infile = fopen("data", "r");
    /********* reading the number of elements in n_elements  ********/
    fscanf(infile,"%d\n", &n_elements);
    buffer = realloc(buffer, n_elements * sizeof(double));
//     double buffer[n_elements];
    for(int i=0; i < n_elements; i++)
      buffer[i] = 0;

    /*** storing each element in buffer[i]   *****/
    for (int i=0; i < n_elements; ++i)
    {
        fscanf(infile,"%lf\n", &buffer[i]);
        printf("Lendo %f\n", *(buffer+i));
    }


    int i, counter=1;
    for (i=0; i < n_elements; i++){
             printf("Flutter->%f %lu\n", buffer[i], sizeof(buffer));
    }

  return 0;
}
