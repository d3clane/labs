#include "GenerateTests.h"

#include <stdlib.h>
#include <time.h>

void GenerateTests(size_t arraySize, int maxElement)
{
    srand((unsigned int)clock());

    for (size_t i = 0; i < arraySize; ++i)
    {
        printf("%d ", rand() % (maxElement + 1));
    }
}