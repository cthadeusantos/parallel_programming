#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {

  // Input reading for process 0
  int n_elements = 5;
  double *buffer;
    /********* reading the number of elements in n_elements  ********/
    buffer = double[n_elements];
    
    for (int i=0; i < n_elements; ++i){
      /*** storing each element in buffer[i]   *****/
      scanf("Entre um valor: %lf", &buffer[i]);
    }
    for (int i=0; i < n_elements; ++i)
      /*** storing each element in buffer[i]   *****/
      printf("valor: %lf", buffer[i]);
  }