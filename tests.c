#include <time.h>

#include "tests.h"
#include "stackOnArr.h"
#include "stackOnList.h"

static const int StandardSize = 1e6;

double TestStackOnArr1()
{
    StackOnArr* stk = StackOnArrCtor(1, sizeof(int));

    clock_t startTime = clock();

    size_t numberOfIterations = 0;

    for (int i = 0; i < StandardSize; ++i)
    {
        StackOnArrPush(stk, &i);
        ++i;
    }

    size_t stackSize = 0;
    while (1)
    {
        stackSize = StackOnArrGetSize(stk);

        if (stackSize <= 1e5)
            break;
        
        for (int i = 0; i < (stackSize / 2); ++i)
            StackOnArrPop(stk);

        for (int i = 0; i < (stackSize / 4); ++i)
            StackOnArrPush(stk, &i);
    }

    return (double)(clock() - startTime) / (double)CLOCKS_PER_SEC;
}

double TestStackOnList1 ()
{
    StackOnList* stk = StackOnListCtor(sizeof(int));

    clock_t startTime = clock();

    for (int i = 0; i < StandardSize; ++i)
        StackOnListPush(stk, &i);

    size_t stackSize = 0;
    while (1)
    {
        stackSize = StackOnListGetSize(stk);

        if (stackSize <= 1e5)
            break;
        
        for (int i = 0; i < (stackSize / 2); ++i)
            StackOnListPop(stk);

        for (int i = 0; i < (stackSize / 4); ++i)
            StackOnListPush(stk, &i);
    }

    return (double)(clock() - startTime) / (double)CLOCKS_PER_SEC;
}

double TestStackOnList2()
{

}

double TestStackOnArr2 ()
{

}

double TestStackOnList3()
{

}

double TestStackOnArr3 ()
{

}

double TestStackOnList4(size_t n)
{

}

double TestStackOnArr4 (size_t n)
{
}
