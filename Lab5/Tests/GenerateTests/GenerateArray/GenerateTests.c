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
