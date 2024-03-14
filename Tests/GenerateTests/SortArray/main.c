#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int QsortCmp(const void* value1, const void* value2)
{
    const int* val1 = (const int*)value1;
    const int* val2 = (const int*)value2;

    return (*val1 - *val2);
}

int main(const int argc, const char* argv[])
{
    assert(argc == 2);

    char* argvValEndPtr = NULL;
    size_t arraySize = strtoul(argv[1], &argvValEndPtr, 10);
    assert(argvValEndPtr != argv[1]);

    int* inputArray = (int*)calloc(arraySize, sizeof(*inputArray));

    for (size_t i = 0; i < arraySize; ++i)
        scanf("%d", inputArray + i);

    qsort(inputArray, arraySize, sizeof(*inputArray), QsortCmp);

    for (size_t i = 0; i < arraySize; ++i)
        printf("%d ", inputArray[i]);
}