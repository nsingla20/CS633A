// Timing codes

#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

int main( int argc, char *argv[])
{
    int myrank;
    MPI_Status status;
    double sTime, eTime, time, maxTime;

    MPI_Init(&argc, &argv);

    int count = atoi (argv[1]);
    char *buf=(char*)malloc(sizeof(char)*count);

    MPI_Comm_rank(MPI_COMM_WORLD, &myrank) ;

    // initialize data
    for (int i=0; i<count; i++)
        buf[i] = myrank;
    sTime = MPI_Wtime();
    if (myrank == 0)
        MPI_Send (buf, count, MPI_BYTE, 1, 1, MPI_COMM_WORLD);
    else
    if (myrank == 1)
        MPI_Recv (buf, count, MPI_BYTE, 0, 1, MPI_COMM_WORLD, &status);
    eTime = MPI_Wtime();
    time = eTime - sTime;
    MPI_Reduce (&time, &maxTime, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
    if(myrank ==0 ){
        printf ("%d", (int)(maxTime*1000000));
    }
    MPI_Finalize();
    return 0;

}

