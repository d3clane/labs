#ifndef TESTS_H
#define TESTS_H

#include <time.h>
#include <stdlib.h>

#include "tests.h"
#include "Array/stackOnArr.h"
#include "List/stackOnList.h"

static const int StandardSize = 1e6;
static const size_t testRepetitionRate = 5;

#define TestStackList(TestNumber, res, ...)                              \
    TestStack##TestNumber(StackOnList, StackOnListCtor, StackOnListDtor, \
                          StackOnListPush, StackOnListPop, StackOnListGetSize, res, __VA_ARGS__)
#define TestStackArr(TestNumber, res, ...)                            \
    TestStack##TestNumber(StackOnArr, StackOnArrCtor, StackOnArrDtor, \
                          StackOnArrPush, StackOnArrPop, StackOnArrGetSize, res, __VA_ARGS__)

#define TestStack1(StackType, Ctor, Dtor, Push, Pop, GetSize, res, ...)              \
    do                                                                               \
    {                                                                                \
        clock_t startTime = clock();                                                 \
                                                                                     \
        for (size_t testNumber = 0; testNumber <= testRepetitionRate; ++testNumber)  \
        {                                                                            \
            StackType *stk = Ctor(sizeof(int));                                      \
            for (int i = 0; i < StandardSize; ++i)                                   \
            {                                                                        \
                Push(stk, &i);                                                       \
                ++i;                                                                 \
            }                                                                        \
                                                                                     \
            size_t stackSize = 0;                                                    \
            while (1)                                                                \
            {                                                                        \
                stackSize = GetSize(stk);                                            \
                                                                                     \
                if (stackSize <= (size_t)1e5)                                        \
                    break;                                                           \
                                                                                     \
                for (int i = 0; i < (int)(stackSize / 2); ++i)                       \
                    Pop(stk);                                                        \
                                                                                     \
                for (int i = 0; i < (int)(stackSize / 4); ++i)                       \
                    Push(stk, &i);                                                   \
            }                                                                        \
            Dtor(stk);                                                               \
        }                                                                            \
        res = (double)(clock() - startTime) / (CLOCKS_PER_SEC * testRepetitionRate); \
    } while (0)

#define TestStack2(StackType, Ctor, Dtor, Push, Pop, GetSize, res, ...)              \
    do                                                                               \
    {                                                                                \
                                                                                     \
        clock_t startTime = clock();                                                 \
        for (size_t testNumber = 0; testNumber < testRepetitionRate; ++testNumber)   \
        {                                                                            \
            StackType *stk = Ctor(sizeof(int));                                      \
            for (int i = 0; i < StandardSize; ++i)                                   \
                Push(stk, &i);                                                       \
                                                                                     \
            for (int i = 0; i < 100; ++i)                                            \
            {                                                                        \
                for (int j = 0; j < 10000; ++j)                                      \
                    Pop(stk);                                                        \
                                                                                     \
                for (int j = 0; j < 10000; ++j)                                      \
                    Push(stk, &j);                                                   \
            }                                                                        \
                                                                                     \
            size_t stackSize = 0;                                                    \
            while (1)                                                                \
            {                                                                        \
                stackSize = GetSize(stk);                                            \
                                                                                     \
                if (stackSize <= (size_t)1e5)                                        \
                    break;                                                           \
                                                                                     \
                for (int i = 0; i < (int)(stackSize / 2); ++i)                       \
                    Pop(stk);                                                        \
                                                                                     \
                for (int i = 0; i < (int)(stackSize / 4); ++i)                       \
                    Push(stk, &i);                                                   \
            }                                                                        \
                                                                                     \
            for (int i = 0; i < 100; ++i)                                            \
            {                                                                        \
                for (int j = 0; j < 10000; ++j)                                      \
                    Pop(stk);                                                        \
                                                                                     \
                for (int j = 0; j < 10000; ++j)                                      \
                    Push(stk, &j);                                                   \
            }                                                                        \
                                                                                     \
            Dtor(stk);                                                               \
        }                                                                            \
                                                                                     \
        res = (double)(clock() - startTime) / (CLOCKS_PER_SEC * testRepetitionRate); \
    } while (0)

#define TestStack3(StackType, Ctor, Dtor, Push, Pop, GetSize, res, ...)            \
    do                                                                             \
    {                                                                              \
        srand(time(NULL));                                                         \
                                                                                   \
        clock_t fullTime = 0;                                                      \
                                                                                   \
        for (size_t testNumber = 0; testNumber < testRepetitionRate; ++testNumber) \
        {                                                                          \
            StackType *stk = Ctor(sizeof(int));                                    \
                                                                                   \
            for (int i = 0; i < StandardSize; ++i)                                 \
                Push(stk, &i);                                                     \
                                                                                   \
            clock_t startTime = clock();                                           \
                                                                                   \
            for (int i = 0; i < StandardSize; ++i)                                 \
            {                                                                      \
                if (rand() % 2 == 0)                                               \
                    Pop(stk);                                                      \
                else                                                               \
                    Push(stk, &i);                                                 \
            }                                                                      \
                                                                                   \
            fullTime += clock() - startTime;                                       \
            Dtor(stk);                                                             \
        }                                                                          \
                                                                                   \
        res = (double)(fullTime) / (CLOCKS_PER_SEC * testRepetitionRate);          \
    } while (0)

#define TestStack4(StackType, Ctor, Dtor, Push, Pop, GetSize, res, n, ...)           \
    do                                                                               \
    {                                                                                \
        clock_t startTime = clock();                                                 \
        for (size_t testNumber = 0; testNumber < testRepetitionRate; ++testNumber)   \
        {                                                                            \
            StackType *stk = Ctor(sizeof(int));                                      \
                                                                                     \
            for (size_t i = 0; i < (size_t)n; ++i)                                   \
            {                                                                        \
                int toPush = (int)i;                                                 \
                                                                                     \
                Push(stk, &toPush);                                                  \
            }                                                                        \
                                                                                     \
            Dtor(stk);                                                               \
        }                                                                            \
        res = (double)(clock() - startTime) / (CLOCKS_PER_SEC * testRepetitionRate); \
    } while (0)

#endif