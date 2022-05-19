#include <omp.h>

void main() {
int x = 5;
//#pragma omp parallel
#pragma omp parallel private(x)
{
    x = x + 1;
    printf("shared : x is %d\n",x );
}

}
