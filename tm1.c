/*
 * You must install openMPI library
 *
 * Compile with:
 * mpicc tm1.c -o output
 *
 * Run using:
 * mpirun -n X output
 * or
 * mpirun -np X output
 *
 * where arg X is the processors' numbers.
 * if  the message "There are not enough slots available in the system to satisfy the X slots that were requested by the application" are returned, add --oversubscribe at mpirun arguments.
 *
 * Known BUGs
 * 
 *In MacOS if you have trouble like this,
 *--------------------------------------------------------------------------
 *A system call failed during shared memory initialization that should
 *not have.  It is likely that your MPI job will now either abort or
 *experience performance degradation.
 *
 *Local host:  guppy01
 *System call: unlink(2) /dev/shm/osc_rdma.guppy01.fd690001.4
 *Error:       No such file or directory (errno 2)
 *--------------------------------------------------------------------------
 *
 * This is a well-known issue with max filename lengths on MacOS.
 * You can >>> export TMPDIR=/tmp <<< (at terminal) to avoid this problem.
 * 
 * Thanks jsquyres at https://github.com/open-mpi/ompi/issues/5798
 */

/*
****************** RELATO ***************
Sistema imac late 2012, 12GB, core i5 (4 núcleos), 2,9GHz
Usando -np 58 funcionou sem erros

Com -np acima de 60 começaram os erros,
msg "The system limit on number of pipes a process can open was reached in file ...."
Onde .... representa a indicação de alguns arquivos

Ficando travado e só saindo com ctrl+C

Com -np 72 além da msg anterior, apareceu outra msg,
mpirun: Forwarding signal 19 to job
Ficando travado e só saindo com ctrl+C

Com -np 128, mesmas mensagens anteriores
Mas agora apareceu a msg MPI_errors_are_fatal
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mpi.h"

int main(int argc, char **argv)
{
    int rank, size, value;
    int destino; 
    char msg[100];
    MPI_Status status;
    MPI_Init( &argc, &argv );
    MPI_Comm_size( MPI_COMM_WORLD, &size ); // Obtem o numero de tarefas

    // numero de tarefas impar, finaliza execução 
    if ((size % 2)!=0){ 
        printf("O numero de processos precisa ser par!\n");
        MPI_Finalize();
        return(0);
    } 
    
    MPI_Comm_rank( MPI_COMM_WORLD, &rank ); // obtem o ranking da tarefa
    // printf("Iniciando processo %d....\n", rank);

    if (rank < size / 2){
        destino = (size/2) + rank;
        MPI_Send(&rank, 1, MPI_INT, destino, 0, MPI_COMM_WORLD);
        MPI_Recv(&rank, 1, MPI_INT, destino, 0, MPI_COMM_WORLD, &status);
    } else {
        destino = abs((size/2) - rank);
        MPI_Send(&rank, 1, MPI_INT, destino, 0, MPI_COMM_WORLD);
        MPI_Recv(&rank, 1, MPI_INT, destino, 0, MPI_COMM_WORLD, &status);
    }
    printf("Tarefa %d enviou seu id para %d\n", rank, destino);

    MPI_Finalize();
}

/*
TM1 - Troca de mensagens em MPI

1) Crie um programa MPI que seja SPMD e realize os seguintes passos:
- Incluir o arquivo header apropriado
- Identificar a tarefa de rank igual a 0 como a tarefa "MESTRE"
- Inicializar o ambiente MPI
- Obter o número total de tarefas
- Obter o ranking da tarefa
- Verificar se a quantidade de tarefas é um número par e terminar o programa caso não seja.
- comentar todo o seu programa devidamente .

- Definindo o programa:
>> Todas as tarefas devem definir uma outra tarefa para enviar uma mensagem bloqueante que será recebida de forma bloqueante pela outra tarefa. Para definir a tarefa destino, a tarefa fonte verifica se o ranking dela é menor que a metade do número de tarefas.
-- Em caso positivo, a tarefa destino será definida como a tarefa que tenha o ranking igual ao valor dado pela metade das tarefas somado com o identificador da tarefa fonte.
-- Em caso negativo, a tarefa destino será definida como a tarefa que tenha o ranking igual ao valor dado pela metade das tarefas subtraído do identificador da tarefa fonte.

>> Cada tarefa deve enviar à sua tarefa destino uma única mensagem contendo um número inteiro indicando seu ranking
>> Cada tarefa destino recebe da sua tarefa fonte uma única mensagem de inteiro com o ranking da tarefa fonte

- Após o envio / recepção, cada tarefa imprime algo como 
"Tarefa XX enviou seu id para YY" 
onde XX é o identificador da tarefa fonte e YY é o identificador da tarefa destino.

2) Teste o seu programa variando o número de processadores
3) Relate os acertos e erros ocorridos e suas observações em relação à execução do programa variando o número de processadores.
*/