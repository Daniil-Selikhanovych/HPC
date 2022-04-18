#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

double * vector(int N, double add)
{
    double *x = (double *)malloc(N*sizeof(double));
    for (int i = 0; i < N; i++)
    {
        x[i] = rand() / (double) RAND_MAX + add;
    }
    return x;
}

double ** matrix(int N)
{
    srand(time(NULL));
    double s;
    double **A = (double **)malloc(N*sizeof(double *));
    for (int i = 0; i < N; i++)
    {
        A[i] = (double *)malloc(N*sizeof(double));
    }
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            A[i][j] = rand() / (double) RAND_MAX;
        }
    }
    for (int i = 0; i < N; i++)
    {
        s = 0;
        for (int j = 0; j < N; j++)
        {
            if (i != j)
            {
                s += A[i][j];
            }
        }
        A[i][i] += s + 1;
    }
    return A;
}

double error_square(double *x1, double *x2, int N)
{
    double err = 0;
    for (int i = 0; i < N; i++)
    {
        err += (x1[i] - x2[i])*(x1[i] - x2[i]);
    }
    return err;
}

void copy(double *x1, double *x2, int N)
{
    for (int i = 0; i < N; i++)
    {
        x2[i] = x1[i];
    }
}

int main()
{
    int N = 1000;
    double e = 1e-5, not_ii;
    double **A, *b, *x, *out;

    double start, end;
    omp_set_num_threads(2);
    int chunk = N/4;
    int j;

    A = matrix(N);
    b = vector(N, 1.);
    x = vector(N, 0.001);
    out = vector(N, 0.);

    int count = 0;
    start = omp_get_wtime();
    while (error_square(x, out, N) > e)
    {
        copy(out, x, N);
        for (int i = 0; i < N; i++)
        {
            not_ii = 0;
            #pragma omp parallel for reduction(+: not_ii) \
                schedule(dynamic, chunk) \
                private(j)
            for (j = 0; j < N; j++)
            {
                if (i != j)
                {
                    not_ii += A[i][j]*x[j];
                }
            }
            out[i] = 1./A[i][i]*(b[i] - not_ii);
        }
        count++;
    }
    end = omp_get_wtime();

    printf("Jacobi method results:\n");
    printf("Error: %f\n", error_square(x, out, N));
    printf("Time: %f\n", (double)(end - start));
    printf("Iterations: %d\n", count);
    return 0;
}