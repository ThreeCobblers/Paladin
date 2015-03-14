#ifndef CACU_PTHREADPOOL_H
#define CACU_PTHREADPOOL_H
/* synchronized jobs list */
//typedef struct cacu_threadpool_job_t cacu_threadpool_job_t;
typedef struct
{
    cacu_threadpool_job_t   **list;
    int                     i_max_size;
    int                     i_size;
    cacu_pthread_mutex_t    mutex;
    cacu_pthread_cond_t     cv_fill;
    cacu_pthread_cond_t     cv_empty;
} cacu_sync_job_list_t;

cacu_threadpool_job_t *cacu_job_shift(cacu_threadpool_job_t **);
void cacu_job_delete_list(cacu_threadpool_job_t **);
int cacu_sync_job_list_init(cacu_sync_job_list_t *, int);
void cacu_sync_job_list_delete(cacu_sync_job_list_t *);
void cacu_sync_job_list_push(cacu_sync_job_list_t *, cacu_threadpool_job_t *);
cacu_threadpool_job_t *cacu_sync_job_list_pop(cacu_sync_job_list_t *);

#endif
