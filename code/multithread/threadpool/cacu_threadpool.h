#ifndef CACU_THREADPOOL_H
#define CACU_THREADPOOL_H
typedef struct cacu_threadpool_t cacu_threadpool_t;

int   cacu_threadpool_init(cacu_threadpool_t **, int,
                            void (*)(void *), void *);
void  cacu_threadpool_run(cacu_threadpool_t *, void *(*)(void *), void *);
void *cacu_threadpool_wait(cacu_threadpool_t *, void *);
void  cacu_threadpool_delete(cacu_threadpool_t *pool );

#endif

