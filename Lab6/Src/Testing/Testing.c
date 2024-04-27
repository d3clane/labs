#include "Testing.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

static inline void ReadFromFile(FILE* inStream, int* arr, size_t arrSize);

void TestTree(const char* testsInsertsDir, const char* testsDeleteDir,
              const char* testsInsertsResFileName, const char* testsDeletesResFileName,
              size_t fromIns, size_t toIns, size_t stepIns, size_t numberOfTestsIns,
              size_t fromDel, size_t toDel, size_t stepDel, size_t numberOfTestsDel,
              TreeType (*Ctor)(), void (*Dtor)(TreeType* tree),
              void (*Insert)(TreeType* tree, int key), 
              void (*Delete)(TreeType* tree, int key))
{
    #define MAX_FILE_NAME_SIZE 256

    static char inFileName[MAX_FILE_NAME_SIZE] = "";

    int* arr = (int*)calloc(toIns, sizeof(*arr));
    assert(arr);
    
    FILE* outStream = fopen(testsInsertsResFileName, "w");
    assert(outStream);

    TreeType tree = Ctor();

    for (size_t arrSize = fromIns; arrSize <= toIns; arrSize += stepIns)
    {
        double averageTime = 0;

        snprintf(inFileName,  MAX_FILE_NAME_SIZE, "%s/%zu.in",  testsInsertsDir, arrSize);
        FILE* inStream = fopen(inFileName, "r");
        assert(inStream);

        ReadFromFile(inStream, arr, arrSize);

        for (size_t k = 1; k <= numberOfTestsIns; ++k)
        {
            clock_t insertTime = clock();

            for (size_t i = 0; i < arrSize; ++i)
                Insert(&tree, arr[i]);

            insertTime = clock() - insertTime;
            averageTime += (double)insertTime / CLOCKS_PER_SEC;
        }

        averageTime /= numberOfTestsIns;
        
        fclose(inStream);

        fprintf(outStream, "%zu %.15lf\n", arrSize, averageTime);
    }

    free(arr);
    fclose(outStream);

    arr = (int*)calloc(toDel, sizeof(*arr));
    assert(arr);
    
    FILE* outStream = fopen(testsDeletesResFileName, "w");
    assert(outStream);

    for (size_t arrSize = fromDel; arrSize <= toDel; arrSize += stepDel)
    {
        double averageTime = 0;

        snprintf(inFileName,  MAX_FILE_NAME_SIZE, "%s/%zu.in",  testsDeleteDir, arrSize);
        FILE* inStream = fopen(inFileName, "r");
        assert(inStream);

        ReadFromFile(inStream, arr, arrSize);

        for (size_t k = 1; k <= numberOfTestsDel; ++k)
        {
            clock_t delTime = clock();

            for (size_t i = 0; i < arrSize; ++i)
                Delete(&tree, arr[i]);

            delTime = clock() - delTime;
            averageTime += (double)delTime / CLOCKS_PER_SEC;
        }

        averageTime /= numberOfTestsIns;
        
        fclose(inStream);

        fprintf(outStream, "%zu %.15lf\n", arrSize, averageTime);
    }

    Dtor(&tree);

    #undef MAX_FILE_NAME_SIZE
}

static inline void ReadFromFile(FILE* inStream, int* arr, size_t arrSize)
{
    assert(inStream);
    assert(arr);

    for (size_t i = 0; i < arrSize; ++i)
        fscanf(inStream, "%d", arr + i);
}
