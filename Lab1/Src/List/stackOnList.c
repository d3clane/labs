#include "stackOnList.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

StackOnList* StackOnListCtor(size_t elemSize)
{
    StackOnList* stk = (StackOnList*) calloc(1, sizeof(*stk));
    assert(stk);
    
    stk->data     = ListCtor(elemSize);

    return stk;
}

StackOnList* StackOnListDtor(StackOnList* stk)
{
    assert(stk);

    ListDtor(&stk->data);

    free(stk);

    return NULL;
}

int StackOnListPush(StackOnList* stk, void* buffer)
{
    assert(stk);
    assert(buffer);

    ListElem* elem = ListInsert(&stk->data, stk->data.begin, buffer);

    return elem == NULL ? 0 : 1;
}

int StackOnListTop (StackOnList* stk, void* buffer)
{
    assert(stk);
    assert(buffer);

    ListElem* elem = ListGetHead(&stk->data);

    if (elem == NULL)
        return 0;
    
    memcpy(buffer, ListGetVal(elem), stk->data.elemSize);

    return 1;
}

int StackOnListPop (StackOnList* stk)
{
    assert(stk);

    return ListPopHead(&stk->data);
}

size_t StackOnListGetSize(StackOnList* stk)
{
    assert(stk);

    return stk->data.size;
}