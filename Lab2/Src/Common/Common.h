#ifndef COMMON_H
#define COMMON_H

#include <assert.h>

static inline void Swap(int* val1, int* val2)
{
    assert(val1);
    assert(val2);
    
    int tmp = *val1;

    *val1 = *val2;
    *val2 = tmp;
}

#endif