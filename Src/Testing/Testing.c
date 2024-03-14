#include "Testing.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

static inline void ReadFromFile(FILE* inStream, int* arr, size_t arrSize);
static inline bool ArraysAreEqual(int* arr1, int* arr2, size_t arrSize);

double* TestSort(const char* testsFromDir, const char* testsResFileName, 
                size_t from, size_t to, size_t step, size_t numberOfTests,
                void (*sort)(int* arr, size_t arrSize))
{
    #define MAX_FILE_NAME_SIZE 256

    fprintf(stderr, "HERE\n");

    static char  inFileName[MAX_FILE_NAME_SIZE] = "";

    int* arr        = (int*)calloc(to, sizeof(*arr));
    int* sortedArr  = (int*)calloc(to, sizeof(*sortedArr));

    double* timeArr = (double*)calloc(((to - from) / step + 1) * numberOfTests, sizeof(*timeArr));
    size_t  timeArrPos = 0;

    FILE* outStream = fopen(testsResFileName, "w");
    assert(outStream);
    fprintf(stderr, "out file name - %s\n", testsResFileName);
    for (size_t arrSize = from; arrSize <= to; arrSize += step)
    {
        for (size_t k = 1; k <= numberOfTests; ++k)
        {
            snprintf(inFileName,  MAX_FILE_NAME_SIZE, "%s/%zu_%zu.in",  
                                                        testsFromDir, arrSize, k);
            
            fprintf(stderr, "in file name - %s\n", inFileName);
            FILE* inStream = fopen(inFileName, "r");
            assert(inStream);

            ReadFromFile(inStream, arr, arrSize);

            clock_t sortTime = clock();
            sort(arr, arrSize);
            sortTime = clock() - sortTime;

            fclose(inStream);

            snprintf(inFileName,  MAX_FILE_NAME_SIZE, "%s/%zu_%zu.out",  
                                                        testsFromDir, arrSize, k);
            fprintf(stderr, "in file name - %s\n", inFileName);

            inStream = fopen(inFileName, "r");
            assert(inStream);

            ReadFromFile(inStream, sortedArr, arrSize);

            assert(ArraysAreEqual(arr, sortedArr, arrSize));

            fclose(inStream);

            fprintf(outStream, "%zu %lf\n", arrSize, (double)sortTime / CLOCKS_PER_SEC);

            timeArr[timeArrPos++] = (double)sortTime / CLOCKS_PER_SEC;
        }
    }

    free(arr);
    free(sortedArr);

    #undef MAX_FILE_NAME_SIZE

    fclose(outStream);
    return timeArr;
}

static inline void ReadFromFile(FILE* inStream, int* arr, size_t arrSize)
{
    assert(inStream);
    assert(arr);

    for (size_t i = 0; i < arrSize; ++i)
        fscanf(inStream, "%d", arr + i);
}

static inline bool ArraysAreEqual(int* arr1, int* arr2, size_t arrSize)
{
    for (size_t i = 0; i < arrSize; ++i)
        if (arr1[i] != arr2[i])
            return false;

    return true;    
}