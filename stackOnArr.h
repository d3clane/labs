#ifndef STACK_ON_ARR_H
#define STACK_ON_ARR_H

#include <stddef.h>
#include "dynamicArr.h"

typedef struct StackOnArr
{
    Array data;
} StackOnArr;

StackOnArr* StackOnArrCtor(size_t size, size_t elemSize);
StackOnArr* StackOnArrDtor(StackOnArr* stk);

int StackOnArrPush(StackOnArr* stk, void* buffer);
int StackOnArrTop (StackOnArr* stk, void* buffer);
int StackOnArrPop (StackOnArr* stk);

size_t StackOnArrGetSize(StackOnArr* stk);

#endif
