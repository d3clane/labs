#if STACK_TYPE == STACK_ON_LIST

#include "stackOnList.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Stack* StackCtor(size_t elemSize)
{
    Stack* stk = (Stack*) calloc(1, sizeof(*stk));
    assert(stk);
    
    stk->data     = ListCtor(elemSize);

    return stk;
}

Stack* StackDtor(Stack* stk)
{
    assert(stk);

    ListDtor(&stk->data);

    free(stk);

    return NULL;
}

int StackPush(Stack* stk, void* buffer)
{
    assert(stk);
    assert(buffer);

    ListElem* elem = ListInsert(&stk->data, stk->data.begin, buffer);

    return elem == NULL ? 0 : 1;
}

int StackTop (Stack* stk, void* buffer)
{
    assert(stk);
    assert(buffer);

    ListElem* elem = ListGetHead(&stk->data);

    if (elem == NULL)
        return 0;
    
    memcpy(buffer, ListGetVal(elem), stk->data.elemSize);

    return 1;
}

int StackPop (Stack* stk)
{
    assert(stk);

    return ListPopHead(&stk->data);
}

size_t StackGetSize(Stack* stk)
{
    assert(stk);

    return stk->data.size;
}

#endif