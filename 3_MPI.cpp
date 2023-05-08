#include <stdio.h>
#include <mpi.h>
//TODO reedit with homework req
#define N 10000
#define ROOT 0

int main(int argc, char* argv[])
{
    int rank, size, i;
    long double result = 0.0, sum = 0.0, begin = 0.0, end = 0.0, x;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Barrier(MPI_COMM_WORLD);
    begin = MPI_Wtime();

    for (i = rank; i < N; i += size)
    {
        x = (i + 0.5) / N;
        result += 4.0 / (1.0 + x * x);
    }

    MPI_Reduce(&result, &sum, 1, MPI_LONG_DOUBLE, MPI_SUM, ROOT, MPI_COMM_WORLD);
    end = MPI_Wtime();

    MPI_Barrier(MPI_COMM_WORLD);

    if (rank == ROOT)
        printf("Time=%fs\nPI=%lf\n", end - begin, sum / N);
    
    MPI_Finalize();
    return 0;
}