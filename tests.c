#include <time.h>
#include <stdlib.h>

#include "tests.h"
#include "stackOnArr.h"
#include "stackOnList.h"

static const int StandardSize = 1e6;

double TestStackOnArr1()
{
    StackOnArr* stk = StackOnArrCtor(1, sizeof(int));

    clock_t startTime = clock();

    for (int i = 0; i < StandardSize; ++i)
    {
        StackOnArrPush(stk, &i);
        ++i;
    }

    size_t stackSize = 0;
    while (1)
    {
        stackSize = StackOnArrGetSize(stk);

        if (stackSize <= (size_t)1e5)
            break;
        
        for (int i = 0; i < (int)(stackSize / 2); ++i)
            StackOnArrPop(stk);

        for (int i = 0; i < (int)(stackSize / 4); ++i)
            StackOnArrPush(stk, &i);
    }

    StackOnArrDtor(stk);

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

        if (stackSize <= (size_t)1e5)
            break;
        
        for (int i = 0; i < (int)(stackSize / 2); ++i)
            StackOnListPop(stk);

        for (int i = 0; i < (int)(stackSize / 4); ++i)
            StackOnListPush(stk, &i);
    }

    StackOnListDtor(stk);

    return (double)(clock() - startTime) / (double)CLOCKS_PER_SEC;
}

double TestStackOnList2()
{
    StackOnList* stk = StackOnListCtor(sizeof(int));

    clock_t startTime = clock();

    for (int i = 0; i < StandardSize; ++i)
        StackOnListPush(stk, &i);

    for (int i = 0; i < 100; ++i)
    {
        for (int j = 0; j < 10000; ++j)
            StackOnListPop(stk);
        
        for (int j = 0; j < 10000; ++j)
            StackOnListPush(stk, &j);
    }

    size_t stackSize = 0;
    while (1)
    {
        stackSize = StackOnListGetSize(stk);

        if (stackSize <= (size_t)1e5)
            break;
        
        for (int i = 0; i < (int)(stackSize / 2); ++i)
            StackOnListPop(stk);

        for (int i = 0; i < (int)(stackSize / 4); ++i)
            StackOnListPush(stk, &i);
    }

    for (int i = 0; i < 100; ++i)
    {
        for (int j = 0; j < 10000; ++j)
            StackOnListPop(stk);
        
        for (int j = 0; j < 10000; ++j)
            StackOnListPush(stk, &j);
    }

    StackOnListDtor(stk);

    return (double) (clock() - startTime) / (double) CLOCKS_PER_SEC;
}

double TestStackOnArr2 ()
{
    StackOnArr* stk = StackOnArrCtor(1, sizeof(int));

    clock_t startTime = clock();

    for (int i = 0; i < StandardSize; ++i)
        StackOnArrPush(stk, &i);

    for (int i = 0; i < 100; ++i)
    {
        for (int j = 0; j < 10000; ++j)
            StackOnArrPop(stk);
        
        for (int j = 0; j < 10000; ++j)
            StackOnArrPush(stk, &j);
    }

    size_t stackSize = 0;
    while (1)
    {
        stackSize = StackOnArrGetSize(stk);

        if (stackSize <= (size_t)1e5)
            break;
        
        for (int i = 0; i < (int)(stackSize / 2); ++i)
            StackOnArrPop(stk);

        for (int i = 0; i < (int)(stackSize / 4); ++i)
            StackOnArrPush(stk, &i);
    }

    for (int i = 0; i < 100; ++i)
    {
        for (int j = 0; j < 10000; ++j)
            StackOnArrPop(stk);
        
        for (int j = 0; j < 10000; ++j)
            StackOnArrPush(stk, &j);
    }

    StackOnArrDtor(stk);

    return (double) (clock() - startTime) / (double) CLOCKS_PER_SEC;
}

double TestStackOnList3()
{
    StackOnList* stk = StackOnListCtor(sizeof(int));
    srand(time(NULL));

    for (int i = 0; i < StandardSize; ++i)
        StackOnListPush(stk, &i);
    
    clock_t startTime = clock();

    for (int i = 0; i < StandardSize; ++i)
    {
        if ((((rand() % 2) + 2) % 2) == 0)
            StackOnListPop(stk);
        else
            StackOnListPush(stk, &i);
    }

    StackOnListDtor(stk);

    return (double) (clock() - startTime) / (double) CLOCKS_PER_SEC;
}

double TestStackOnArr3 ()
{
    StackOnArr* stk = StackOnArrCtor(1, sizeof(int));
    srand(time(NULL));

    for (int i = 0; i < StandardSize; ++i)
        StackOnArrPush(stk, &i);
    
    clock_t startTime = clock();

    for (int i = 0; i < StandardSize; ++i)
    {
        if ((((rand() % 2) + 2) % 2) == 0)
            StackOnArrPop(stk);
        else
            StackOnArrPush(stk, &i);
    }

    StackOnArrDtor(stk);

    return (double) (clock() - startTime) / (double) CLOCKS_PER_SEC;
}

double TestStackOnArr4 (size_t n)
{
    StackOnArr* stk = StackOnArrCtor(1, sizeof(int));

    clock_t startTime = clock();

    for (size_t i = 0; i < n; ++i)
    {
        int toPush = (int)i;

        StackOnArrPush(stk, &toPush);
    }

    StackOnArrDtor(stk);

    return (double)(clock() - startTime) / (double) CLOCKS_PER_SEC;
}

double TestStackOnList4(size_t n)
{
    StackOnList* stk = StackOnListCtor(sizeof(int));

    clock_t startTime = clock();

    for (size_t i = 0; i < n; ++i)
    {
        int toPush = (int)i;

        StackOnListPush(stk, &toPush);
    }

    StackOnListDtor(stk);

    return (double)(clock() - startTime) / (double) CLOCKS_PER_SEC;
}
