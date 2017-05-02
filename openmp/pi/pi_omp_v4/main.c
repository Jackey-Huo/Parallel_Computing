#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define MAX_THRD       200

static long long num_steps = 100000000;
double step;

int main()
{
    int i, ret;
    int tnum, tid;
    double localSum[MAX_THRD];
    double sumLocal;
    double x, tmp_x, pi, sum = 0.0;

    struct timeval start, stop;

    step = 1.0/(double)num_steps;
    ret = gettimeofday(&start, NULL);
    if(ret != 0)
    {
        printf("start time error, exit program\n");
        exit(-1);
    }

    #pragma omp parallel shared(tnum, localSum) private(tid, sumLocal, x, tmp_x)
    {
        tid = omp_get_thread_num();
        if (tid == 0)
        {
            tnum = omp_get_num_threads();
            if(tnum > MAX_THRD)
            {
                printf("Error: too many threads, the maximum of thread number is %d\n", MAX_THRD);
                exit(-1);
            }
        }

        sumLocal = 0;
        #pragma omp for
        for(i = 0; i < num_steps; ++i)
        {
            x = (i + 0.5) * step;
            tmp_x = 4.0/(1.0 + x*x);
            sumLocal = sumLocal + tmp_x;
        }

        localSum[tid] = sumLocal;
        printf("in thread %d, localSum[%d] = %lf\n", tid, tid, localSum[tid]);
    }

    for (i = 0; i < tnum; ++i)
    {
        sum += localSum[i];
    }

    ret = gettimeofday(&stop, NULL);
    if(ret != 0)
    {
        printf("stop time error, exit program\n");
        exit(-1);
    }
    pi = step * sum;

    printf("pi = %20.17lf\n", pi);
    printf("time used to calculate pi is %f microseconds\n", ((double)(stop.tv_sec - start.tv_sec)*1000000 + (double)(stop.tv_usec - start.tv_usec)));

    return 0;
}
