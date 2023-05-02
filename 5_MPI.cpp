#include <stdio.h>
#include <mpi.h>

#define a 0
#define b 5
#define N 1000000
#define ROOT 0
//f(x) = x^3

int main(int argc, char* argv[])
{
    int rank, size, i;
    long double result = 0.0, sum = 0.0, begin = 0.0, end = 0.0, x;
    long double h = (b - a) / (long double)N, y = 0.0;
    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Barrier(MPI_COMM_WORLD);
    begin = MPI_Wtime();

    for (i = rank; i < N; i += size)
        y += (i * h) * (i * h) * (i * h);
    
    MPI_Reduce(&y, &sum, 1, MPI_LONG_DOUBLE, MPI_SUM, ROOT, MPI_COMM_WORLD);
    end = MPI_Wtime();

    MPI_Barrier(MPI_COMM_WORLD);

    if (rank == ROOT)
        printf("Time = %fs\ny = %lf\n", end - begin, sum * h);
    
    MPI_Finalize();
    return 0;
}