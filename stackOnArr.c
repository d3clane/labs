#include <assert.h>
#include <stdlib.h>

#include "stackOnArr.h"
#include "dynamicArr.h"

StackOnArr* StackOnArrCtor(size_t size, size_t elemSize)
{
    StackOnArr* stk = calloc(1, sizeof(*stk));
    stk->data = ArrayInit(size, elemSize);

    return stk;
}

StackOnArr* StackOnArrDtor(StackOnArr* stk)
{
    assert(stk);
    ArrayDtor(&stk->data);

    free(stk);

    return NULL;
}

int StackOnArrPush(StackOnArr* stk, void* buffer)
{
    assert(stk);
    assert(buffer);

    return ArrayPushBack(&stk->data, buffer);
}

int StackOnArrTop (StackOnArr* stk, void* buffer)
{
    assert(stk);
    assert(buffer);

    if (stk->data.size == 0)
        return 0;

    buffer = ArrayGetVal(&stk->data, stk->data.size - 1);

    return 1;
}

int StackOnArrPop (StackOnArr* stk)
{
    assert(stk);

    return ArrayPopBack(&stk->data);
}
