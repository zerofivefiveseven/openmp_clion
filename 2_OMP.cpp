//2
#include <stdio.h>
#include <omp.h>

#define pthread 12
#define a 0
#define b 5
#define N 1000000//number of iterations - accuracy
//https://www.integral-calculator.ru/
//f(x) = x^3
int main(int argc, char** argv)
{
    int i;
    long double h = (b - a) / (long double)N, y = 0.0, start, time;
    start = omp_get_wtime();
#pragma omp parallel for num_threads(pthread)
    for (i = 0; i < N; ++i)
        y += (i * h) * (i * h) * (i * h);
    time = omp_get_wtime() - start;
    printf("Time = %lf \ny = %f", time, y * h);
    return 0;
}
