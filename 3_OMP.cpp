//4
#include <stdio.h>
#include <omp.h>
#include <unistd.h>
#include <math.h>
#define acc 0.00000000001
#define N 100000
#define pthread 4
#define ee 2.718281828459045
#define pp 3.1415926535
int main(int argc, char** argv)
{
    bool flag = true;
    int i;
    long double x = 0.0, pi = 0.0, start = 0.0, time = 0.0 ,e;
    start = omp_get_wtime();
#pragma omp parallel for private(x) num_threads(pthread)
    for (i = 1; i < N; ++i)
    {
        if (!flag) continue;
        if(abs(pi - pp) < acc && abs(e - ee) < acc){
            flag = false;}
        x = (i + 0.5) / N;
#pragma omp critical
        pi += 4 / (1 + x * x);
        e = pow((1+(1/(long double)i)),i);
    }
    time = omp_get_wtime() - start;
    printf("Time = %Lf\npi = %Lf\ne = %Lf", time, pi / N, e);
    return 0;
}