#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

double ** create_matrix(double a, double b, int N)
{
        double ** A = (double **) malloc(sizeof(double*)*N);
        for (int i = 0; i < N; i++)
        {
                A[i] = (double *)malloc(sizeof(double)*2);
        } 
        for (int i = 0; i < N; i++)
        {
                A[i][0] = i* rand() / (double) RAND_MAX;
                A[i][1] = a*A[i][0] + b + rand() / (double) RAND_MAX;
        }
    return A;
}

int main()
{
    int N = 10000, n_steps = 10000;
    double a = 3., b = 4.;
    double a_g, b_g, a_n, b_n;
    
    a_n = rand() / RAND_MAX;
    b_n = rand() / RAND_MAX;
    
    double ** A;    
    A = create_matrix(a, b, N);
    
    double lr = 1e-5;

    int i;
    double start, end;
    omp_set_num_threads(2);
    start = omp_get_wtime();
    for (int step = 0; step < n_steps; step++)
    {
        a_g = 0.;
        b_g = 0.;
        #pragma omp parallel for reduction(+: a_g) \
                     reduction(+: b_g) \
                     schedule(static) \
                     private(i)
        for (i = 0; i < N; i++)
        {
            a_g += -2*(A[i][1] - a_n*A[i][0] - b_n)*A[i][0];
            b_g += -2*(A[i][1] - a_n*A[i][0] - b_n);
        }
        a_n -= lr*a_g;
        b_n -= lr*b_g;
    }
    end = omp_get_wtime();
    printf("Estimated a: %f, b: %f, true a: %f, b: %f\n", a_n, b_n, a, b);
    printf("time: %f\n", (double)(end - start));
    return 0;
}
