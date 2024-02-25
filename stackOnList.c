#include "stackOnList.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

StackOnList* StackOnListCtor(size_t elemSize)
{
    StackOnList* stk = (StackOnList*) calloc(1, sizeof(*stk));

    stk->data     = ListCtor();
    stk->elemSize = elemSize;

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

    ListElem* elem = ListInsert(&stk->data, stk->data.begin, buffer, stk->elemSize);

    return elem == NULL ? 0 : 1;
}

int StackOnListTop (StackOnList* stk, void* buffer)
{
    assert(stk);
    assert(buffer);

    ListElem* elem = ListGetHead(&stk->data);

    if (elem == NULL)
        return 0;
    
    buffer = ListGetVal(elem);

    return 1;
}

int StackOnListPop (StackOnList* stk)
{
    assert(stk);

    return ListPopHead(&stk->data);
}
