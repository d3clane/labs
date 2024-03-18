#include <time.h>
#include <stdlib.h>

#include "tests.h"
#include "Array/stackOnArr.h"
#include "List/stackOnList.h"

static const int StandardSize = 1e6;
static const size_t testRepetitionRate = 5;

double TestStack1()
{
    clock_t startTime = clock();

    for (size_t testNumber = 0; testNumber <= testRepetitionRate; ++testNumber)
    {
        Stack *stk = StackCtor(sizeof(int));
        for (int i = 0; i < StandardSize; ++i)
        {
            StackPush(stk, &i);
            ++i;
        }

        size_t stackSize = 0;
        while (1)
        {
            stackSize = StackGetSize(stk);

            if (stackSize <= (size_t)1e5)
                break;

            for (int i = 0; i < (int)(stackSize / 2); ++i)
                StackPop(stk);

            for (int i = 0; i < (int)(stackSize / 4); ++i)
                StackPush(stk, &i);
        }
        StackDtor(stk);
    }
    return (double)(clock() - startTime) / (CLOCKS_PER_SEC * testRepetitionRate);
}

double TestStack2()
{
    clock_t startTime = clock();
    for (size_t testNumber = 0; testNumber < testRepetitionRate; ++testNumber)
    {
        Stack *stk = StackCtor(sizeof(int));
        for (int i = 0; i < StandardSize; ++i)
            StackPush(stk, &i);

        for (int i = 0; i < 100; ++i)
        {
            for (int j = 0; j < 10000; ++j)
                StackPop(stk);

            for (int j = 0; j < 10000; ++j)
                StackPush(stk, &j);
        }

        size_t stackSize = 0;
        while (1)
        {
            stackSize = StackGetSize(stk);

            if (stackSize <= (size_t)1e5)
                break;

            for (int i = 0; i < (int)(stackSize / 2); ++i)
                StackPop(stk);

            for (int i = 0; i < (int)(stackSize / 4); ++i)
                StackPush(stk, &i);
        }

        for (int i = 0; i < 100; ++i)
        {
            for (int j = 0; j < 10000; ++j)
                StackPop(stk);

            for (int j = 0; j < 10000; ++j)
                StackPush(stk, &j);
        }

        StackDtor(stk);
    }

    return (double)(clock() - startTime) / (CLOCKS_PER_SEC * testRepetitionRate);
}

double TestStack3()
{
    srand(time(NULL));

    clock_t fullTime = 0;

    for (size_t testNumber = 0; testNumber < testRepetitionRate; ++testNumber)
    {
        Stack *stk = StackCtor(sizeof(int));

        for (int i = 0; i < StandardSize; ++i)
            StackPush(stk, &i);

        clock_t startTime = clock();

        for (int i = 0; i < StandardSize; ++i)
        {
            if (rand() % 2 == 0)
                StackPop(stk);
            else
                StackPush(stk, &i);
        }

        fullTime += clock() - startTime;
        StackDtor(stk);
    }

    return (double)(fullTime) / (CLOCKS_PER_SEC * testRepetitionRate);
}

void   TestStack4(FILE* outStream)
{
    for (size_t n = 1000; n < (size_t)1e6; n += 1000)
    {
        clock_t startTime = clock();
        for (size_t testNumber = 0; testNumber < testRepetitionRate; ++testNumber)
        {
            Stack *stk = StackCtor(sizeof(int));

            for (size_t i = 0; i < (size_t)n; ++i)
            {
                int toStackPush = (int)i;

                StackPush(stk, &toStackPush);
            }

            StackDtor(stk);
        }
        
        fprintf(outStream, "%zu, %lf\n", n, 
                    (double)(clock() - startTime) / (CLOCKS_PER_SEC * testRepetitionRate));
    }
}
