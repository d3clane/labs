#ifndef STACK_ON_LIST_H
#define STACK_ON_LIST_H

#include <stddef.h>
#include "list.h"

typedef struct StackOnList
{
    List data;
} StackOnList;

StackOnList* StackOnListCtor(size_t elemSize);
StackOnList* StackOnListDtor(StackOnList* stk);

int StackOnListPush(StackOnList* stk, void* buffer);
int StackOnListTop (StackOnList* stk, void* buffer);
int StackOnListPop (StackOnList* stk);

size_t StackOnListGetSize(StackOnList* stk);

#endif