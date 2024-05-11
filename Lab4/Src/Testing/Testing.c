#include "Testing.h"
#include "Heap/Heap.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

static inline void ReadFromFile(FILE* inStream, int* arr, size_t arrSize);
static inline bool ArraysIsValid(int* arr, size_t arrSize);

double* TestHeap(const char* testsFromDir, const char* testsResFileName, 
                size_t from, size_t to, size_t step, size_t numberOfTests,
                void (*Heap)(int* arr, size_t arrSize))
{
    #define MAX_FILE_NAME_SIZE 256

    static char  inFileName[MAX_FILE_NAME_SIZE] = "";

    int* arr        = (int*)calloc(to, sizeof(*arr));
    int* sortedArr  = (int*)calloc(to, sizeof(*sortedArr));

    double* timeArr = (double*)calloc(((to - from) / step + 1) * numberOfTests, sizeof(*timeArr));
    size_t  timeArrPos = 0;

    assert(arr);
    assert(sortedArr);
    assert(timeArr);

    FILE* outStream = fopen(testsResFileName, "w");
    assert(outStream);

    for (size_t arrSize = from; arrSize <= to; arrSize += step)
    {
        double averageTime = 0;
        for (size_t k = 1; k <= numberOfTests; ++k)
        {
            snprintf(inFileName,  MAX_FILE_NAME_SIZE, "%s/%zu_%zu.in",  
                                                        testsFromDir, arrSize, k);
            
            FILE* inStream = fopen(inFileName, "r");
            assert(inStream);

            ReadFromFile(inStream, arr, arrSize);

            clock_t sortTime = clock();
            Heap(arr, arrSize);
            sortTime = clock() - sortTime;
            averageTime += (double)sortTime / CLOCKS_PER_SEC;

            fclose(inStream);

            assert(ArraysIsValid(arr, arrSize));

            timeArr[timeArrPos++] = (double)sortTime / CLOCKS_PER_SEC;
        }
        averageTime /= numberOfTests;
        
        fprintf(outStream, "%zu %.15lf\n", arrSize, averageTime);
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

static inline bool ArraysIsValid(int* arr, size_t arrSize)
{
    Heap heap = HeapCtor(arr, arrSize);

    assert(HeapIsValid(&heap));

    HeapDtor(&heap);

    return true;    
}