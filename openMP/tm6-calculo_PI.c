// O Algoritmo abaixo, calcula PI. 
// A cada iteração do loop while (!done) cálculos de PI são realizados e comparados com PI25DT, sendo o erro calculado e mostrado. 
// 1) O que acontece se a cada iteração, o usuário aumento o número de intervalos? 
// 2) Varie o número de processos
// 3) Responda as perguntas abaixo
//
//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h> 
#include <mpi.h>

int main(argc,argv)
int argc;
char *argv[];
{
    /* inicialização */
    int done = 0, n, myid, numprocs, i;
    double PI25DT = 3.141592653589793238462643;
    double mypi, pi, h, sum, x;

    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD,&myid);

    while (!done){
    if (myid == 0) {   /* o mestre coleta o número de intervalos */
        printf("Entre o numero de intervalos: (0 termina) ");
        fflush(stdout);        
        scanf("%d",&n);

    }

    /* o que está acontecendo aqui ?? */
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);  

    if (n == 0) break;
      h   = 1.0 / (double) n;  /* 1o intervalo */
    sum = 0.0;
    /* o que cada processo faz?  */
    /* acumula os proximos n-1 intervalos */
    for (i = myid + 1; i <= n; i += numprocs) { 
        x = h * ((double)i - 0.5);
        sum += 4.0 / (1.0 + x*x);
    }

    mypi = h * sum;
    /* o que acontece aqui? */
      MPI_Reduce(&mypi, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);  

    /* finalizando */
  
    if (myid == 0){
        printf("pi is approximately %.16f, Error is %.16f\n", 
            pi, fabs(pi - PI25DT));
    }
        
}


    MPI_Finalize();
}