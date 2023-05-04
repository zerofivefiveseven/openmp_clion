#include <omp.h>
#include <cstdint> //int64_t
//5
#include <iostream>

#define N 4
using namespace std;

int main()
{
    int64_t n = 100;
    //cout << "n = ";
    //cin >> n;
    int64_t* a = new int64_t[n + 1];
    long double start = 0.0, time = 0.0;

    start = omp_get_wtime();
#pragma omp parallel for shared(a, n) num_threads(N)
        for (int64_t i = 0; i < n + 1; i++)
            a[i] = i;

#pragma omp parallel for shared(a, n) num_threads(N)
    for (int64_t p = 2; p < n + 1; p++)
    {
        if (a[p] != 0)
        {
            //cout << a[p] << endl;
            for (int64_t j = p * p; j < n + 1; j += p)
                a[j] = 0;
        }
    }
    time = omp_get_wtime() - start;
    cout << "time = " << time << "\n";
    return 0;
}
