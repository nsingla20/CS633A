#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]) {

	int myrank, numtasks;

	// Setup
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	// MPI_Status status;
	// MPI_Datatype newvtype;

	int px = atoi( argv[1] );
	int py = atoi( argv[2] );
	long long int N = atoi( argv[3] );
	long long int x=N/px, y=N/py;
	int no_itr=10;

	double data[x][y];
	double sTime, eTime, time, max_time;

	long long int of_x = (myrank%px)*x, of_y = (myrank/px)*y;
	long long int send_l=(of_y+y-of_x>0)?(of_y+y-of_x):0;
	long long int recv_l=(send_l-y>0)?(send_l-y):0;
	if(send_l>x)send_l=x;
	if(recv_l>x)recv_l=x;
	// printf("%d: Send %d, Recv %d\n",myrank,send_l,recv_l);
	// initialize data
	for (long long int i=0; i<x; i++)
		for (long long int j=0; j<y; j++)
			data[i][j] = rand() /10.0;        // check for using srand()

	double recv[recv_l];

	MPI_Request request;
	MPI_Status status;
	sTime = MPI_Wtime();
	for(int itr=0;itr<no_itr;itr++){
		for(int i=y-2;i>0;i--){
			for(int j=0;j<x;j++){
				if(of_x+j > of_y+i)break;
				data[i][j] -= data[i-1][j];
			}
		}
		if(myrank < px){
			MPI_Isend(&data[y-1][0],send_l,MPI_DOUBLE,myrank+px,myrank+px,MPI_COMM_WORLD,&request);
		}
		else if(myrank >= px && myrank < px*(py - 1)){
			MPI_Isend(&data[y-1][0],send_l,MPI_DOUBLE,myrank+px,myrank+px,MPI_COMM_WORLD,&request);
			MPI_Recv(recv,recv_l,MPI_DOUBLE,myrank-px,myrank,MPI_COMM_WORLD,&status);
			for(int j=0; j < recv_l; j++){
				if(of_x+j > of_y)break;
				data[0][j] -= recv[j];
			}
		}else{
			MPI_Recv(recv,recv_l,MPI_DOUBLE,myrank-px,myrank,MPI_COMM_WORLD,&status);
			for(int j=0; j < recv_l; j++){
				if(of_x+j > of_y)break;
				data[0][j] -= recv[j];
			}
		}
		if(y>1){
			for(int j=0;j<x;j++){
				if(of_x+j > of_y+y-1)break;
				data[y-1][j] -= data[y-2][j];
			}
		}
		MPI_Barrier (MPI_COMM_WORLD);
	}
	eTime = MPI_Wtime();
	time = eTime - sTime;

	MPI_Reduce (&time, &max_time, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
	if(!myrank) printf ("%lf", max_time);

	// MPI_Type_free (&newvtype);
	// finalize
	MPI_Finalize();

	return 0;
}
