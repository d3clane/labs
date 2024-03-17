#include "GenerateTests.h"

#include <assert.h>
#include <stdlib.h>

int main(const int argc, const char* argv[])
{
    assert(argc == 3);

    char* argvValEndPtr = NULL;
    size_t arraySize = strtoul(argv[1], &argvValEndPtr, 10);
    assert(argvValEndPtr != argv[1]);

    int maxVal = (int)strtol(argv[2], &argvValEndPtr, 10);
    assert(argvValEndPtr != argv[2]);

    GenerateTests(arraySize, maxVal);
}