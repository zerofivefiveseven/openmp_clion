#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#define NN 4
static char isPrime[10000000];

static int eratosthenesOdd(long int N)
{

    omp_set_num_threads(NN);

    /* instead of i*i <= N we write i <= sqr(N) to help OpenMP */
    const int NSqrt = (int)sqrt((double)N);
    int memorySize = (N - 1) / 2;

    int i, j;
    /* Let all numbers be prime initially */
#pragma omp parallel num_threads(NN)
    for (i = 0; i <= memorySize; i++)
    {
        isPrime[i] = 1;
    }


    /* find all odd non-primes */
    #pragma omp parallel for
    for (i = 3; i <= NSqrt; i += 2)
    {
        if (isPrime[i / 2])
        {
            for (j = i * i; j <= N; j += 2 * i)
            {
                isPrime[j / 2] = 0;
            }
        }
    }


    printf("2\n");
    for (int k = 3; k <= N; k += 2)
    {
        if (isPrime[k / 2] == 1)
        {
            printf("%d\n", k);
        }
    }

    /* sieve is complete, count primes */
    int total = N >= 2 ? 1 : 0;
    #pragma omp parallel for reduction(+:total)
    for (i = 1; i <= memorySize; i++)
    {
        total += isPrime[i];
    }
return total;

}

int main(void)
{
    long double start,time;
    start = omp_get_wtime();


    int total = eratosthenesOdd(1000000);
    time = omp_get_wtime() - start;
    printf("Number of primes: %d\n", total);
    printf("Time = %Lf",time);

    return 0;
}