#include "mpi.h"
#include <iostream>
#include <unistd.h>

static int gsize, rank;

int main(int argc, char* argv[]) 
{
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &gsize);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
		
	printf("Hello, World! I'm thread %d from %d threads\n", rank, gsize);

    sleep(1000); //sleep(1); ��� ����
		if ((rank & 1) == 0)
			printf("I'm thread %d. I'm even.\n", rank);

	MPI_Finalize();
	return 0;
}