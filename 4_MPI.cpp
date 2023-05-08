#include <stdio.h>
#include <mpi.h>
#include <math.h>

#define N 100
#define ROOT 0
//TODO reedit with homework req
int is_prime(int n)
{
    int top, d;
    top = (int)(sqrt((double)n) + 0.0001);
    for (d = 2; d <= top; d++)
        if (n % d == 0)
            return 0;
    return 1;
}

int main(int argc, char* argv[])
{
    int rank, size, i;
    long double begin = 0.0, end = 0.0;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Barrier(MPI_COMM_WORLD);

    begin = MPI_Wtime();

    for (i = rank + 2; i < N; i += size)
        if (is_prime(i))
            printf("%d\n", i);

    end = MPI_Wtime();

    if (rank == ROOT)
        printf("Time=%fs\n", end - begin);

    MPI_Finalize();
    return 0;
}