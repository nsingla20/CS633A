// Timing codes

#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

int main( int argc, char *argv[])
{
    int myrank;
    MPI_Status status;
    double sTime, eTime, time, d;

    MPI_Init(&argc, &argv);

    int count = atoi (argv[1]);
    char buf[count];

    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

    // initialize data
    for (int i=0; i<count; i++)
        buf[i] = myrank+i;
    MPI_Barrier(MPI_COMM_WORLD);
    sTime = MPI_Wtime();
    if (myrank == 0)
        MPI_Send (buf, count, MPI_BYTE, 1, 1, MPI_COMM_WORLD);
    else
    if (myrank == 1)
        MPI_Recv (buf, count, MPI_BYTE, 0, 1, MPI_COMM_WORLD, &status);
    eTime = MPI_Wtime();
    d = eTime-sTime;
    MPI_Reduce (&d, &time, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
    if(myrank ==0 ){
        printf ("%lf",time);
    }
    MPI_Finalize();
    return 0;

}

