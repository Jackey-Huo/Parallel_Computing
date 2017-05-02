#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

static long long num_steps = 10000000;
double step;

int main()
{
    int i, ret;
    double x, tmp_x, pi, sum = 0.0;

    struct timeval start, stop;

    step = 1.0/(double)num_steps;
    ret = gettimeofday(&start, NULL);
    if(ret != 0)
    {
        printf("start time error, exit program\n");
        exit(-1);
    }

    #pragma omp parallel for
    for(i=0; i < num_steps; ++i)
    {
        x = (i + 0.5) * step;
        tmp_x = 4.0/(1.0 + x*x);
        #pragma omp critical
        sum = sum + tmp_x;
    }

    ret = gettimeofday(&stop, NULL);
    if(ret != 0)
    {
        printf("stop time error, exit program\n");
        exit(-1);
    }
    pi = step * sum;

    printf("pi = %20.17lf\n", pi);
    printf("time used to calculate pi is %f microseconds\n", ((double)(stop.tv_sec - start.tv_sec)*1000 + (double)(stop.tv_usec - start.tv_usec)));

    return 0;
}
