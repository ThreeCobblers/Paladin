#include "common.h"

cacu_threadpool_job_t *cacu_job_shift(cacu_threadpool_job_t **list)
{
    cacu_threadpool_job_t *job = list[0];
    for(int i = 0; list[i]; i++)
        list[i] = list[i + 1];
    return job;
}

void cacu_job_delete_list(cacu_threadpool_job_t **list)
{
    int i = 0;
    if(!list)
        return;
    while(list[i]) cacu_free(list[i++]);
    cacu_free(list);
}

int cacu_sync_job_list_init(cacu_sync_job_list_t *slist, int max_size)
{
    if(max_size < 0)
        return -1;
    slist->i_max_size = max_size;
    slist->i_size = 0;
    CHECKED_MALLOCZERO(slist->list, (max_size + 1) * sizeof(cacu_threadpool_job_t *));
    if(cacu_pthread_mutex_init(&slist->mutex, NULL) ||
       cacu_pthread_cond_init(&slist->cv_fill, NULL) ||
       cacu_pthread_cond_init(&slist->cv_empty, NULL))
        return -1;
    return 0;
fail:
	return -1;
}

void cacu_sync_job_list_delete(cacu_sync_job_list_t *slist)
{
    cacu_pthread_mutex_destroy(&slist->mutex);
    cacu_pthread_cond_destroy(&slist->cv_fill);
    cacu_pthread_cond_destroy(&slist->cv_empty);
    cacu_job_delete_list(slist->list);
}

void cacu_sync_job_list_push(cacu_sync_job_list_t *slist, cacu_threadpool_job_t *job)
{
    cacu_pthread_mutex_lock(&slist->mutex);
    while(slist->i_size == slist->i_max_size)
        cacu_pthread_cond_wait(&slist->cv_fill, &slist->mutex);
    slist->list[slist->i_size++] = job;
    cacu_pthread_mutex_unlock(&slist->mutex);
    cacu_pthread_cond_broadcast(&slist->cv_fill);
}

cacu_threadpool_job_t *cacu_sync_job_list_pop(cacu_sync_job_list_t *slist)
{
    cacu_threadpool_job_t *job;
    cacu_pthread_mutex_lock(&slist->mutex);
    while(!slist->i_size)
        cacu_pthread_cond_wait(&slist->cv_fill, &slist->mutex);
    job = slist->list[--slist->i_size];
    slist->list[slist->i_size] = NULL;
    cacu_pthread_cond_broadcast(&slist->cv_empty);
    cacu_pthread_mutex_unlock(&slist->mutex);
    return job;
}
