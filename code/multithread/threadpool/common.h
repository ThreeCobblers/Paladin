#ifndef CACU_COMMON_H
#define CACU_COMMON_H

#define CHECKED_MALLOC( var, size )\
do {\
    var = cacu_malloc( size );\
    if( !var )\
        goto fail;\
} while( 0 )
#define CHECKED_MALLOCZERO( var, size )\
do {\
    CHECKED_MALLOC( var, size );\
    memset( var, 0, size );\
} while( 0 )

#include <pthread.h>
#define cacu_pthread_t               pthread_t
#define cacu_pthread_create          pthread_create
#define cacu_pthread_join            pthread_join
#define cacu_pthread_self			 pthread_self
#define cacu_pthread_mutex_t         pthread_mutex_t
#define cacu_pthread_mutex_init      pthread_mutex_init
#define cacu_pthread_mutex_destroy   pthread_mutex_destroy
#define cacu_pthread_mutex_lock      pthread_mutex_lock
#define cacu_pthread_mutex_unlock    pthread_mutex_unlock
#define cacu_pthread_cond_t          pthread_cond_t
#define cacu_pthread_cond_init       pthread_cond_init
#define cacu_pthread_cond_destroy    pthread_cond_destroy
#define cacu_pthread_cond_broadcast  pthread_cond_broadcast
#define cacu_pthread_cond_wait       pthread_cond_wait
#define cacu_pthread_attr_t          pthread_attr_t
#define cacu_pthread_attr_init       pthread_attr_init
#define cacu_pthread_attr_destroy    pthread_attr_destroy
#define cacu_pthread_num_processors_np pthread_num_processors_np
#define CACU_PTHREAD_MUTEX_INITIALIZER PTHREAD_MUTEX_INITIALIZER

typedef struct
{
    void *(*func)(void *);
    void *arg;
    void *ret;
} cacu_threadpool_job_t;

#include <stdlib.h>
#include <string.h>
#include "cacu_job.h"
#include "cacu_threadpool.h"

void *cacu_malloc( int );
void  cacu_free( void * );

#endif
