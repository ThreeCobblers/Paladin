#include <stdio.h>
#include "common.h"

#if 0
/* job */
typedef struct
{
    void *(*func)(void *);
    void *arg;
    void *ret;
} cacu_threadpool_job_t;
#endif

/* threadpool */
struct cacu_threadpool_t
{
    int             exit;
    int             threads;
    cacu_pthread_t  *thread_handle;
    void            (*init_func)(void *);
    void            *init_arg;

    cacu_sync_job_list_t uninit;
    cacu_sync_job_list_t run;
    cacu_sync_job_list_t done; /* useless here */    
};

static void *cacu_threadpool_thread(cacu_threadpool_t *pool)
{
    if(pool->init_func) pool->init_func(pool->init_arg);

#if 1
    printf("thread id %8u was created successly \n", (unsigned int)cacu_pthread_self() % 10000);
#endif
    while(!pool->exit)
    {
        cacu_threadpool_job_t *job = NULL;
        cacu_pthread_mutex_lock(&pool->run.mutex);
        while(!pool->exit && !pool->run.i_size)
            cacu_pthread_cond_wait(&pool->run.cv_fill, &pool->run.mutex);
        if(pool->run.i_size)
        {
            job = (void *)cacu_job_shift(pool->run.list);
            pool->run.i_size--;
        }
        cacu_pthread_mutex_unlock(&pool->run.mutex);
        if(!job)
            continue;
        job->ret = job->func(job->arg);
        cacu_sync_job_list_push(&pool->uninit, (void *)job);
    }
#if 1
    printf("thread id %8u exited successly \n", (unsigned int)cacu_pthread_self() % 10000);
#endif
    return NULL;
}

int cacu_threadpool_init(cacu_threadpool_t **p_pool, int threads,
                         void (*init_func)(void *), void *init_arg)
{
    if(threads < 0) return -1;

    cacu_threadpool_t *pool;
    CHECKED_MALLOCZERO(pool, sizeof(cacu_threadpool_t));
    *p_pool = pool;

    pool->init_func = init_func;
    pool->init_arg  = init_arg;
    pool->threads   = threads;

    CHECKED_MALLOC(pool->thread_handle, pool->threads * sizeof(cacu_pthread_t));

    if(cacu_sync_job_list_init(&pool->uninit, pool->threads) ||
       cacu_sync_job_list_init(&pool->run, pool->threads) ||
       cacu_sync_job_list_init(&pool->done, pool->threads))
        goto fail;

    for(int i = 0; i < pool->threads; i++)
    {
        cacu_threadpool_job_t *job;
        CHECKED_MALLOC(job, sizeof(cacu_threadpool_job_t));
        cacu_sync_job_list_push(&pool->uninit, (void *)job);
    }

    for(int i = 0; i < pool->threads; i++)
        if(cacu_pthread_create(pool->thread_handle + i, NULL, (void *)cacu_threadpool_thread, pool))
            goto fail;
    return 0;
fail:
    return -1;
}

void cacu_threadpool_run(cacu_threadpool_t *pool, void *(*func)(void *), void *arg)
{
    cacu_threadpool_job_t *job = (void *)cacu_sync_job_list_pop(&pool->uninit);
    job->func = func;
    job->arg  = arg;
    cacu_sync_job_list_push(&pool->run, (void*)job);
}

void *cacu_threadpool_wait(cacu_threadpool_t *pool, void *arg)
{
    cacu_threadpool_job_t *job = NULL;
    cacu_pthread_mutex_lock(&pool->done.mutex);
    while(!job)
    {
        for(int i = 0; i < pool->done.i_size; i++)
        {
            cacu_threadpool_job_t *t = (void *)pool->done.list[i];
            if(t->arg == arg)
            {
                job = (void *)cacu_job_shift(pool->done.list + i);
                pool->done.i_size--;
            }
        }
        if(!job)
            cacu_pthread_cond_wait(&pool->done.cv_fill, &pool->done.mutex);
    }
    cacu_pthread_mutex_unlock(&pool->done.mutex);

    void *ret = job->ret;
    cacu_sync_job_list_push(&pool->uninit, (void *)job);
    return ret;
}

static void cacu_threadpool_list_delete(cacu_sync_job_list_t *slist)
{
    for(int i = 0; slist->list[i]; i++)
    {
        cacu_free((void*)slist->list[i]);
        slist->list[i] = NULL;
    }
}

void cacu_threadpool_delete(cacu_threadpool_t *pool)
{
    cacu_pthread_mutex_lock(&pool->run.mutex);
    pool->exit = 1;
    cacu_pthread_cond_broadcast(&pool->run.cv_fill);
    cacu_pthread_mutex_unlock(&pool->run.mutex);
    for(int i = 0; i < pool->threads; i++)
        cacu_pthread_join(pool->thread_handle[i], NULL);
    cacu_threadpool_list_delete(&pool->uninit);
    cacu_threadpool_list_delete(&pool->run);
    cacu_threadpool_list_delete(&pool->done);
    cacu_free(pool->thread_handle);
    cacu_free(pool);
}
