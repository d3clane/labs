#include <assert.h>
#include <stdlib.h>
#include <string.h>


#include "stackOnArr.h"
#include "dynamicArr.h"

StackOnArr* StackOnArrCtor(size_t elemSize)
{
    return StackOnArrInit(1, elemSize);
}

StackOnArr* StackOnArrInit(size_t size, size_t elemSize)
{
    StackOnArr* stk = (StackOnArr*)calloc(size, sizeof(*stk));
    assert(stk);

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

    memcpy(buffer, ArrayGetVal(&stk->data, stk->data.size - 1), stk->data.elemSize);

    return 1;
}

int StackOnArrPop (StackOnArr* stk)
{
    assert(stk);

    return ArrayPopBack(&stk->data);
}

size_t StackOnArrGetSize(StackOnArr* stk)
{
    assert(stk);

    return stk->data.size;
}
