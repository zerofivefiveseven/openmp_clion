#include <iostream>
#include <cstdlib>
#include <omp.h>
//3
#define pthread 4
#define N 1000

void randomMatrix(int** matrix, int n, int m);

int main(int argc, char** argv)
{
    srand(time(NULL));

    int** matrix1;
    int** matrix2;
    int** result;
    long double start = 0.0, time = 0.0;

    matrix1 = (int**)malloc(sizeof(int*) * N);
    for (int i = 0; i < N; i++) 
        matrix1[i] = (int*)malloc(sizeof(int) * N);
    
    matrix2 = (int**)malloc(sizeof(int*) * N);
    for (int i = 0; i < N; i++) 
        matrix2[i] = (int*)malloc(sizeof(int) * N);
    
    result = (int**)malloc(sizeof(int*) * N);;
    for (int i = 0; i < N; i++)
        result[i] = (int*)malloc(sizeof(int) * N);

    printf("A: \n");
    randomMatrix(matrix1, N, N);
    printf("B: \n");
    randomMatrix(matrix2, N, N);

    int i, j, k;
   
    start = omp_get_wtime();
#pragma omp parallel for shared(matrix1, matrix2, result) private(i, j, k) num_threads(pthread)
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++) 
        {
            result[i][j] = 0;
            for (k = 0; k < N; k++) 
                result[i][j] += (matrix1[i][k] * matrix2[k][j]);
        }
    }
  
    time = omp_get_wtime() - start;
    printf("Time = %lf s\n", time);
    printf("Result: \n");

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
            printf("%d ", result[i][j]);
        printf("\n");
    }

    for (int i = 0; i < N; i++)
    {
        free(matrix1[i]);
        free(matrix2[i]);
        free(result[i]);
    }
    free(matrix1);
    free(matrix2);
    free(result);

    return 0;
}

void randomMatrix(int** matrix, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            matrix[i][j] = rand() % 5;
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}