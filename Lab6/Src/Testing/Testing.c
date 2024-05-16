#include "Testing.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

static inline void ReadFromFile(FILE* inStream, int* arr, size_t arrSize);

volatile TreeType tmp = {};

void TestTree(const char* testsInsertsDir, const char* testsDeleteDir,
              const char* testsInsertsResFile, const char* testsDeletesResFile,
              size_t fromIns, size_t toIns, size_t stepIns, size_t numberOfTestsIns,
              TreeType (*Ctor)(), void (*Dtor)(TreeType* tree),
              void (*Insert)(TreeType* tree, int key), 
              void (*Delete)(TreeType* tree, int key))
{
    #define MAX_FILE_NAME_SIZE 256

    static const size_t delSizeCoeff = 2;

    static char inFileName[MAX_FILE_NAME_SIZE]  = "";

    int* arrIns = (int*)calloc(toIns, sizeof(*arrIns));
    assert(arrIns);
    int* arrDel = (int*)calloc(toIns / delSizeCoeff, sizeof(*arrDel));
    assert(arrDel);

    FILE* outStreamIns = fopen(testsInsertsResFile, "w");
    assert(outStreamIns);

    FILE* outStreamDel = fopen(testsDeletesResFile, "w");
    assert(outStreamDel);

    for (size_t arrSize = fromIns; arrSize <= toIns; arrSize += stepIns)
    {
        fprintf(stderr, "size - %zu\n", arrSize);

        double averageInsTime = 0;
        double averageDelTime = 0;

        for (size_t k = 1; k <= numberOfTestsIns; ++k)
        {
            snprintf(inFileName,  MAX_FILE_NAME_SIZE, "%s/%zu_%zu.in",  testsInsertsDir, arrSize, k);
            FILE* inStreamIns = fopen(inFileName, "r");
            assert(inStreamIns);
            
            ReadFromFile(inStreamIns, arrIns, arrSize);

            snprintf(inFileName,  MAX_FILE_NAME_SIZE, "%s/%zu_%zu.in",  testsDeleteDir, 
                     arrSize / delSizeCoeff, k);
            FILE* inStreamDel = fopen(inFileName, "r");
            assert(inStreamDel);

            ReadFromFile(inStreamDel, arrDel, arrSize / delSizeCoeff);

            TreeType tree = Ctor();

            clock_t insertTime = clock();
            for (size_t i = 0; i < arrSize; ++i)
                Insert(&tree, arrIns[i]);
            insertTime = clock() - insertTime;
    
            averageInsTime += (double)insertTime / CLOCKS_PER_SEC;

            clock_t delTime = clock();
            for (size_t i = 0; i < arrSize / delSizeCoeff; ++i)
                Delete(&tree, arrDel[i]);
            delTime = clock() - delTime;

            averageDelTime += (double)delTime / CLOCKS_PER_SEC;

            tmp.root = tree.root;
            Dtor(&tree);

            fclose(inStreamIns);
            fclose(inStreamDel);
        }

        averageInsTime /= numberOfTestsIns;
        averageDelTime /= numberOfTestsIns;
        
        fprintf(outStreamIns, "%zu %.15lf\n", arrSize, averageInsTime);
        fprintf(outStreamDel, "%zu %.15lf\n", arrSize / delSizeCoeff, averageDelTime);
    }

    fclose(outStreamIns);
    fclose(outStreamDel);
    free(arrIns);
    free(arrDel);

    #undef MAX_FILE_NAME_SIZE
}

static inline void ReadFromFile(FILE* inStream, int* arr, size_t arrSize)
{
    assert(inStream);
    assert(arr);

    for (size_t i = 0; i < arrSize; ++i)
        fscanf(inStream, "%d", arr + i);
}
