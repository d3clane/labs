#include "GenerateTests.h"

#include <assert.h>
#include <stdlib.h>
#include <time.h>

void GenerateTestsInt(size_t arraySize, int maxElement)
{
    srand(42);

    for (size_t i = 0; i < arraySize; ++i)
    {
        printf("%d ", rand() % (maxElement + 1));
    }
}

void GenerateTestsFloat(size_t arraySize, int range)
{
    srand(42);

    for (size_t i = 0; i < arraySize; ++i)
    {
        printf("%lf ", (float)rand() / (float)RAND_MAX * (float)(2 * range) - range);
    }
}

void GenerateTestsStrs(size_t arraySize, size_t lenMin, size_t lenMax)
{
    assert(lenMax >= lenMin);

    srand(42);

    for (size_t i = 0; i < arraySize; ++i)
    {
        size_t strLen = rand() % (lenMax - lenMin + 1) + lenMin;

        for (size_t j = 0; j < strLen; ++j)
            printf("%c", rand() % ('z' - 'a' + 1) + 'a');

        printf("\n");
    }
}

void GenerateTestsOps1(size_t arraySize)
{
    srand(42);

    for (size_t i = 0; i < arraySize; ++i)
    {
        char op = rand() % 3;

        switch (op)
        {
            case 0:
                op = '+';
                break;
            
            case 1:
                op = '-';
                break;

            case 2:
                op = '?';
                break;

            default:
                break;
        }

        int val = rand();

        printf("%c %d\n", op, val);
    }
}

void GenerateTestsOps2(size_t arraySize)
{
    srand(42);

    for (size_t i = 0; i < arraySize; ++i)
    {
        char op = rand() % 4;

        switch (op)
        {
            case 0:
            case 1:
                op = '+';
                break;
            
            case 2:
                op = '-';
                break;

            case 3:
                op = '?';
                break;

            default:
                break;
        }

        int val = rand();

        printf("%c %d\n", op, val);
    }
}
