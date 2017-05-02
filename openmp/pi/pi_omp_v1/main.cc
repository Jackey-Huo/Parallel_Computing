#include <omp.h>
#include <stdio.h>
#include <sys/time.h>

static long long num_steps = 10000000;
double step;

int main()
{
    int i;
    double x, pi, sum = 0.0;

    struct timeval start, stop;

    step = 1.0/(double)num_steps;
    gettimeofday(&start, NULL);

    #pragma omp parallel for reduction(+:sum)
    for(i=0; i < num_steps; ++i)
    {
        x = (i + 0.5) * step;
        sum = sum + 4.0/(1.0 + x*x);
    }

    gettimeofday(&stop, NULL);
    pi = step * sum;

    printf("pi = %20.17lf\n", pi);
    printf("time used to calculate pi is %f microseconds\n", ((double)(stop.tv_sec - start.tv_sec)*1000 + (double)(stop.tv_usec - start.tv_usec)));

    return 0;
}
