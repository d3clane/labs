#include "GenerateTests.h"

#include <assert.h>
#include <stdlib.h>

int main(const int argc, const char* argv[])
{
    assert(argc >= 4);

    char* argvValEndPtr = NULL;
    size_t arraySize = strtoul(argv[2], &argvValEndPtr, 10);
    assert(argvValEndPtr != argv[2]);

    if (argv[1][0] == 'i')
    {
        int maxVal = (int)strtol(argv[3], &argvValEndPtr, 10);
        assert(argvValEndPtr != argv[3]);

        GenerateTestsInt(arraySize, maxVal);
    }
    else if (argv[1][0] == 'f')
    {
        int range = (int)strtol(argv[3], &argvValEndPtr, 10);
        assert(argvValEndPtr != argv[3]);

        GenerateTestsFloat(arraySize, range);
    }
    else if (argv[1][0] == 's')
    {
        size_t lenMin = (int)strtoul(argv[3], &argvValEndPtr, 10);
        assert(argvValEndPtr != argv[3]);

        size_t lenMax = (int)strtoul(argv[4], &argvValEndPtr, 10);
        assert(argvValEndPtr != argv[4]);

        GenerateTestsStrs(arraySize, lenMin, lenMax);
    }
}