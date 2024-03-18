#if STACK_TYPE == STACK_ON_ARR

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "stackOnArr.h"
#include "dynamicArr.h"

Stack* StackCtor(size_t elemSize)
{
    return StackInit(1, elemSize);
}

Stack* StackInit(size_t size, size_t elemSize)
{
    Stack* stk = (Stack*)calloc(size, sizeof(*stk));
    assert(stk);

    stk->data = ArrayInit(size, elemSize);

    return stk;
}

Stack* StackDtor(Stack* stk)
{
    assert(stk);
    ArrayDtor(&stk->data);

    free(stk);

    return NULL;
}

int StackPush(Stack* stk, void* buffer)
{
    assert(stk);
    assert(buffer);

    return ArrayPushBack(&stk->data, buffer);
}

int StackTop (Stack* stk, void* buffer)
{
    assert(stk);
    assert(buffer);

    if (stk->data.size == 0)
        return 0;

    memcpy(buffer, ArrayGetVal(&stk->data, stk->data.size - 1), stk->data.elemSize);

    return 1;
}

int StackPop (Stack* stk)
{
    assert(stk);

    return ArrayPopBack(&stk->data);
}

size_t StackGetSize(Stack* stk)
{
    assert(stk);

    return stk->data.size;
}

#endif