#ifndef STACK_ON_ARR_H
#define STACK_ON_ARR_H

#if STACK_TYPE == STACK_ON_ARR

#include <stddef.h>
#include "dynamicArr.h"

typedef struct Stack
{
    Array data;
} Stack;

Stack* StackInit(size_t size, size_t elemSize);
Stack* StackCtor(size_t elemSize);
Stack* StackDtor(Stack* stk);

int StackPush(Stack* stk, void* buffer);
int StackTop (Stack* stk, void* buffer);
int StackPop (Stack* stk);

size_t StackGetSize(Stack* stk);

#endif 

#endif
