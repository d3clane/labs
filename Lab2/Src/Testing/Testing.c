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
    //fprintf(stderr, "out file name - %s\n", testsResFileName);
    for (size_t arrSize = from; arrSize <= to; arrSize += step)
    {
        double averageTime = 0;
        for (size_t k = 1; k <= numberOfTests; ++k)
        {
            snprintf(inFileName,  MAX_FILE_NAME_SIZE, "%s/%zu_%zu.in",  
                                                        testsFromDir, arrSize, k);
            
            //fprintf(stderr, "in file name - %s\n", inFileName);
            FILE* inStream = fopen(inFileName, "r");
            assert(inStream);

            ReadFromFile(inStream, arr, arrSize);

            clock_t sortTime = clock();
            sort(arr, arrSize);
            sortTime = clock() - sortTime;
            averageTime += (double)sortTime / CLOCKS_PER_SEC;

            fclose(inStream);

            snprintf(inFileName,  MAX_FILE_NAME_SIZE, "%s/%zu_%zu.out",  
                                                        testsFromDir, arrSize, k);
            //fprintf(stderr, "in file name - %s\n", inFileName);

            inStream = fopen(inFileName, "r");
            assert(inStream);

            ReadFromFile(inStream, sortedArr, arrSize);

            assert(ArraysAreEqual(arr, sortedArr, arrSize));

            fclose(inStream);

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

void TestHeapSort(const char* testsFromDir, const char* testsResFileName, 
                  size_t from, size_t to, size_t step, size_t numberOfTests,
                  void (*sort)(int* arr, size_t arrSize, size_t heapRank))
{
    #define MAX_FILE_NAME_SIZE 256


    static char inFileName [MAX_FILE_NAME_SIZE] = "";
    static char outFileName[MAX_FILE_NAME_SIZE] = "";

    int* arr        = (int*)calloc(to, sizeof(*arr));
    int* sortedArr  = (int*)calloc(to, sizeof(*sortedArr));

    assert(arr);
    assert(sortedArr);

    for (size_t heapRank = 2; heapRank <= 15; ++heapRank)
    {
        snprintf(outFileName, MAX_FILE_NAME_SIZE, "%s_%zu", testsResFileName, heapRank);
        FILE* outStream = fopen(outFileName, "w");
        assert(outStream);
        //fprintf(stderr, "out file name - %s\n", outFileName);
        for (size_t arrSize = from; arrSize <= to; arrSize += step)
        {
            double averageTime = 0;
            for (size_t k = 1; k <= numberOfTests; ++k)
            {
                snprintf(inFileName,  MAX_FILE_NAME_SIZE, "%s/%zu_%zu.in",  
                                                            testsFromDir, arrSize, k);
                
                //fprintf(stderr, "in file name - %s\n", inFileName);
                FILE* inStream = fopen(inFileName, "r");
                assert(inStream);

                ReadFromFile(inStream, arr, arrSize);

                clock_t sortTime = clock();
                sort(arr, arrSize, heapRank);
                sortTime = clock() - sortTime;
                averageTime += (double)sortTime / CLOCKS_PER_SEC;

                fclose(inStream);

                snprintf(inFileName,  MAX_FILE_NAME_SIZE, "%s/%zu_%zu.out",  
                                                            testsFromDir, arrSize, k);
                //fprintf(stderr, "in file name - %s\n", inFileName);

                inStream = fopen(inFileName, "r");
                assert(inStream);

                ReadFromFile(inStream, sortedArr, arrSize);

                assert(ArraysAreEqual(arr, sortedArr, arrSize));

                fclose(inStream);
            }
            averageTime /= numberOfTests;
            
            fprintf(outStream, "%zu %.15lf\n", arrSize, averageTime);
        }
        
        fclose(outStream);
    }

    free(arr);
    free(sortedArr);

    #undef MAX_FILE_NAME_SIZE
}

void TestIntroSort(const char* testsFromDir, const char* testsResFileName, 
                  size_t from, size_t to, size_t step, size_t numberOfTests,
                  void (*sort)(int* arr, size_t arrSize, double recursionDepthConstant))
{
    #define MAX_FILE_NAME_SIZE 256

    static char inFileName [MAX_FILE_NAME_SIZE] = "";

    int* arr        = (int*)calloc(to, sizeof(*arr));
    int* sortedArr  = (int*)calloc(to, sizeof(*sortedArr));

    assert(arr);
    assert(sortedArr);
    
    FILE* outStream = fopen(testsResFileName, "w");
    assert(outStream);
    fprintf(stderr, "out file name - %s\n", testsResFileName);
    for (double recursionDepthC = 0.1; recursionDepthC < 20; recursionDepthC += 0.1)
    {
        double time = 0;
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
                sort(arr, arrSize, recursionDepthC);
                sortTime = clock() - sortTime;
                time += (double)sortTime / CLOCKS_PER_SEC;

                fclose(inStream);

                snprintf(inFileName,  MAX_FILE_NAME_SIZE, "%s/%zu_%zu.out",  
                                                            testsFromDir, arrSize, k);
                fprintf(stderr, "in file name - %s\n", inFileName);

                inStream = fopen(inFileName, "r");
                assert(inStream);

                ReadFromFile(inStream, sortedArr, arrSize);

                assert(ArraysAreEqual(arr, sortedArr, arrSize));

                fclose(inStream);
            }
        }
        fprintf(outStream, "%lf %lf\n", recursionDepthC, time);
    }

    fclose(outStream);

    free(arr);
    free(sortedArr);

    #undef MAX_FILE_NAME_SIZE    
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