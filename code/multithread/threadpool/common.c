#include "common.h"

void cacu_free(void *p)
{
    if(p)
        free(p);  
}
void *cacu_malloc(int i_size)
{
    return malloc(i_size);
}
