#include <stdio.h>
#include <omp.h>
#include <time.h>

#define INT_MAX 2147483647

double monte_carlo_pi()
{
    int N_total = 1e7;
    int N_in = 0;
    int counter = 0;
    int cond;
    double start, end;
    float x, y, pi;
    start = omp_get_wtime();

    #pragma omp parallel firstprivate(counter) private(x,y)
    {
        #pragma omp for
        for (int i=0; i<N_total; ++i) {
            x = (float)rand() / INT_MAX;
            y = (float)rand() / INT_MAX;
            cond = (x * x + y * y < 1);
            counter += cond;
            #pragma omp atomic update
            N_in += cond;
        }
    }
    pi = 4 * (float)N_in / N_total;

    end = omp_get_wtime();
    printf("parallel monte-carlo pi = %.16f, time = %f\n", pi, (double)(end - start));
    return pi;
}


int main()
{
    const size_t N = 10000000;
    double step;

    double x, pi, sum = 0.;

    step = 1. / (double)N;

    clock_t start, end;

    start = clock();
    for (int i = 0; i < N; ++i)
    {
        x = (i + 0.5) * step;
        sum += 4.0 / (1. + x * x);
    }
    end = clock();

    pi = step * sum;

    printf("pi = %.16f, time = %f\n", pi, (double)(end - start));
    
    monte_carlo_pi();

    return 0;
}
