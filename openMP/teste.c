#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
 
  int n_elements;
  printf("Elementos a serem lidos:\n");
  scanf("%i\n", &n_elements); 
    
  int rank, size;
  
  FILE *infile;

  // Input reading for process 0

  double buffer[n_elements];
  
    /********* reading the number of elements in n_elements  ********/
//    buffer[n_elements] = {0};
    infile = fopen("data", "r");
    for (int i=0; i < n_elements; ++i)
    {
        fscanf(infile,"%lf\n", &buffer[i]);
        printf("%f\n", buffer[i]);
    }
 
      /*** storing each element in buffer[i]   *****/
}