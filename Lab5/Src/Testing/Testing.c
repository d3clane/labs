#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "HashTable/HashTableOpen.h"
#include "HashTable/HashTableWithList.h"
#include "HashTable/HashTableIdeal.h"
#include "Testing.h"

static inline void ReadFromFile(FILE* inStream, HashValType* arr, size_t arrSize);

#ifdef KNUTH_HASH

static inline size_t HashMod(HashFuncType Hash, size_t MOD, HashValType val)
{
    size_t hash = Hash(val, MOD);

    assert(hash < MOD);

    return hash;
}

#else

static inline size_t HashMod(HashFuncType Hash, size_t MOD, HashValType val)
{
    return Hash(val) % MOD;
}

#endif

double TestHash(const char* inFileName, const char* outFileName,
                size_t numberOfValues, HashFuncType Hash)
{
    HashValType* arr  = (HashValType*)calloc(numberOfValues, sizeof(*arr));
    size_t arrSize    = numberOfValues;
    assert(arr); 

    static const size_t distributionArraySize = 1000;
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

    FILE* outStream = fopen(outFileName, "w");
    assert(outStream);

    for (size_t i = 0; i < distributionArraySize; ++i)
        fprintf(outStream, "%zu %zu\n", i, distribution[i]);

    fclose(inStream);
    fclose(outStream);

    return (double)time / CLOCKS_PER_SEC;
}

#if TYPE == INT_TYPE

#ifndef IDEAL_TABLE

void TestLoadFactor(const char* inFileName, const char* outFileName,
                    size_t numberOfValues,
                    const float minLoadFactor, const float maxLoadFactor, 
                    const float loadFactorStep,
                    HashFuncType Hash)
{
    unsigned int* arr  = (unsigned int*)calloc(numberOfValues, sizeof(*arr));
    size_t arrSize    = numberOfValues;
    assert(arr); 

    FILE* inStream = fopen(inFileName, "r");
    assert(inStream);

    ReadFromFile(inStream, arr, arrSize);

    FILE* outStream = fopen(outFileName, "w");
    assert(outStream);

    for (float loadFactor = minLoadFactor; loadFactor <= maxLoadFactor; 
         loadFactor += loadFactorStep)
    {
        HashTableType* table = HashTableCtor(2, Hash, loadFactor);
        
        clock_t time = clock();
        for (size_t i = 0; i < arrSize; ++i)
            HashTableInsert(table, arr[i]);
        time = clock() - time;

        fprintf(outStream, "%lf %lf\n", loadFactor, (double)time / CLOCKS_PER_SEC);

        HashTableDtor(table);
    }
}

void TestTablesOperations(const char* inFileDir, const char* outFileName,
                           const size_t from, const size_t to, const size_t step,
                           HashFuncType Hash)
{
#define MAX_FILE_NAME_LEN 256
    char inFileName[MAX_FILE_NAME_LEN] = "";

#if defined(LIST_TABLE)
    static const float optimalLoadFactor = 2.75;
#else
    static const float optimalLoadFactor = 0.8;
#endif

    FILE* outStream = fopen(outFileName, "w");
    assert(outStream);

    for (size_t numberOfOperations = from; numberOfOperations <= to; numberOfOperations += step)
    {
        snprintf(inFileName, MAX_FILE_NAME_LEN, "%s/%zu.in", inFileDir, numberOfOperations);

        FILE* inStream = fopen(inFileName, "r");
        assert(inStream);

        clock_t time = 0;

        HashTableType* table = HashTableCtor(1, Hash, optimalLoadFactor);
        for (size_t op = 0; op < numberOfOperations; ++op)
        {
            char opType = 0;
            int val     = 0;

            fscanf(inStream, "%c %d\n", &opType, &val);

            clock_t deltaTime = clock();
            switch (opType)
            {
                case '+':
                    HashTableInsert(table, val);
                    break;
                
                case '-':
                    HashTableErase(table, val);
                    break;

                case '?':
                    HashTableGetValue(table, val);
                    break;

                default:
                    break;
            }

            time += clock() - deltaTime;
        }

        fprintf(outStream, "%zu %lf\n", numberOfOperations, (double)time / CLOCKS_PER_SEC);

        HashTableDtor(table);
        fclose(inStream);
    }

    #undef MAX_FILE_NAME_LEN
}

#endif

double TestTablesSearches(const char* insertValuesFileName, const char* searchValuesFileName,
                          const size_t numberOfInsertedVals, const size_t numberOfSearchingVals)
{
    unsigned int* arr  = (unsigned int*)calloc(numberOfInsertedVals, sizeof(*arr));
    size_t arrSize     = numberOfInsertedVals;
    assert(arr); 

    FILE* inStream = fopen(insertValuesFileName, "r");
    assert(inStream);

    ReadFromFile(inStream, arr, arrSize);

    HashTableType* table = NULL;

#if defined(LIST_TABLE)
    static const float optimalLoadFactor = 2.75;
#else
    static const float optimalLoadFactor = 0.8;
#endif

#ifdef IDEAL_TABLE
    table = HashTableInit(arr, arrSize);
#else
    table = HashTableCtor(1, UniversalHashFixed, optimalLoadFactor);
    for (size_t i = 0; i < arrSize; ++i)
        HashTableInsert(table, arr[i]);
#endif

    fclose(inStream);
    free(arr);
    arr = NULL;

    inStream = NULL;
    inStream = fopen(searchValuesFileName, "r");
    assert(inStream);

    arr = (unsigned int*)calloc(numberOfSearchingVals, sizeof(*arr));
    arrSize = numberOfSearchingVals;
    assert(arr);

    ReadFromFile(inStream, arr, arrSize);

    clock_t time = clock();

    for (size_t i = 0; i < arrSize; ++i)
        HashTableGetValue(table, arr[i]);

    time = clock() - time;

    HashTableDtor(table);
    fclose(inStream);
    free(arr);

    return (double) time / CLOCKS_PER_SEC;
}

#endif

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
