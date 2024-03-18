#ifndef STACK_ON_LIST_H
#define STACK_ON_LIST_H

#if STACK_TYPE == STACK_ON_LIST

#include <stddef.h>
#include "list.h"

typedef struct Stack
{
    List data;
} Stack;

Stack* StackCtor(size_t elemSize);
Stack* StackDtor(Stack* stk);

int StackPush(Stack* stk, void* buffer);
int StackTop (Stack* stk, void* buffer);
int StackPop (Stack* stk);

size_t StackGetSize(Stack* stk);

#endif 

#endif