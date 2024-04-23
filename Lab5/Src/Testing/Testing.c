#include "Testing.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

static inline void ReadFromFile(FILE* inStream, HashValType* arr, size_t arrSize);

static inline size_t HashMod(size_t (*Hash)(HashValType val), size_t MOD, HashValType val)
{
    return Hash(val) % MOD;
}

double TestHash(const char* inFileName, const char* outFileName,
                size_t numberOfValues, HashFuncType Hash)
{
    #define MAX_FILE_NAME_SIZE 256

    HashValType* arr  = (HashValType*)calloc(numberOfValues, sizeof(*arr));
    size_t arrSize    = numberOfValues;
    assert(arr); 

    static const size_t distributionArraySize = 145007;
    size_t* distribution = (size_t*)calloc(distributionArraySize, sizeof(*distribution));
    assert(distribution);

    FILE* inStream = fopen(inFileName, "r");
    assert(inStream);

    ReadFromFile(inStream, arr, arrSize);

    clock_t time = clock();

    for (size_t i = 0; i < arrSize; ++i)
        distribution[HashMod(Hash, distributionArraySize, arr[i])]++;
    time = clock() - time;

#if TYPE == STR_TYPE
    for (size_t i = 0; i < arrSize; ++i)
        free((char*)arr[i]);
#endif

    free(arr);
    free(distribution);

    #undef MAX_FILE_NAME_SIZE

    FILE* outStream = fopen(outFileName, "w");
    assert(outStream);

    for (size_t i = 0; i < distributionArraySize; ++i)
        fprintf(outStream, "%zu %zu\n", i, distribution[i]);

    fclose(inStream);
    fclose(outStream);

    return (double)time / CLOCKS_PER_SEC;
}

static inline void ReadFromFile(FILE* inStream, HashValType* arr, size_t arrSize)
{
    assert(inStream);
    assert(arr);

#if TYPE == STR_TYPE
    size_t bufSize = 0;
    for (size_t i = 0; i < arrSize; ++i)
    {
        ssize_t endPos = getline(arr + i, &bufSize, inStream);
        assert(arr[i][endPos - 1] == '\n');
        arr[i][endPos - 1] = '\0';
    }
#else
    for (size_t i = 0; i < arrSize; ++i)
        fscanf(inStream, HASH_VAL_FORMAT_STR, arr + i);
#endif
}
