#include <stdio.h>
#include <unistd.h>
#include "common.h"

#define MAX_LEN 64
char a[][MAX_LEN] = 
{
    "Add",
    "Sub",
    "Mul",
    "Div",
    "Power",
    "Sqrt"
};
int loop[] = {
    1000,
    1000000000,
    100000,
    100000000,
    100,
    100000,
    1000000000,
    1000,
    10000000,
    100000
};

void* cacu(void *arg)
{
    cacu_pthread_t tid = cacu_pthread_self();
    printf("thread id %8u was started with job of loop %10d times\n", (unsigned int)tid % 10000, *(int *)arg);
    for(int i = 0; i < *(int *)arg; i++);
    printf("thread id %8u was finished after %20d loops\n", (unsigned int)tid % 10000, *(int *)arg);	
    return (void *)0;
}

int main(int argc, char *argv[])
{
    cacu_threadpool_t *pool = NULL;
    int threads = 4;
    cacu_threadpool_init(&pool, threads, NULL, NULL);

    cacu_threadpool_run(pool, cacu, (void *)&loop[0]);

    cacu_threadpool_run(pool, cacu, (void *)&loop[1]);

    cacu_threadpool_run(pool, cacu, (void *)&loop[2]);

    cacu_threadpool_run(pool, cacu, (void *)&loop[3]);

    cacu_threadpool_run(pool, cacu, (void *)&loop[4]);

    cacu_threadpool_run(pool, cacu, (void *)&loop[5]);

    cacu_threadpool_run(pool, cacu, (void *)&loop[6]);

    cacu_threadpool_run(pool, cacu, (void *)&loop[7]);

    cacu_threadpool_run(pool, cacu, (void *)&loop[8]);

    cacu_threadpool_run(pool, cacu, (void *)&loop[9]);

    cacu_threadpool_delete(pool);
    return 0;
}
