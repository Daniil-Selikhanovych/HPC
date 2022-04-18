#include <stdio.h>
#include <omp.h>
#include <time.h>

#define INT_MAX 2147483647

double monte_carlo_pi()
{
    const size_t N = 100000;
    double step;
    double x, pi, sum = 0.;
    step = 1. / (double)N;

    double start, end;
    int darts = 0;
    omp_set_num_threads(2);

    start = omp_get_wtime();
    #pragma omp parallel shared(darts)
    {
        int thread_id = omp_get_thread_num();
        unsigned int seed_x = thread_id;
        unsigned int seed_y = thread_id + 1.;
        double x, y;
        #pragma omp for schedule(dynamic, N / 2) \
            reduction(+: darts) \
            private(x, y)
        for (int i = 0; i < N; ++i)
        {
            x = ((double) rand_r(&seed_x)) / (double) INT_MAX;
            y = ((double) rand_r(&seed_y)) / (double) INT_MAX;

            x = (i + 0.5) * step;
            sum += 4.0 / (1. + x * x);
        }
    }

    pi = step * sum;

    end = omp_get_wtime();
    printf("parallel monte-carlo pi = %.16f, time = %f\n", pi, (double)(end - start));
    return pi;
}


int main()
{
    const size_t N = 100000;
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