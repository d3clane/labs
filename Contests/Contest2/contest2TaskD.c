#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct
{
    int key;

    bool val;
} HashTableElemType;

typedef struct
{
    HashTableElemType* data;
    size_t dataSize;
    size_t dataCapacity;

    int hashFuncA;
    int hashFuncB;
    int hashFuncP;
} HashTableElemsArr;

typedef struct
{
    HashTableElemsArr* buckets;
    size_t numberOfBuckets;

    int hashFuncA;
    int hashFuncB;
    int hashFuncP;
} HashTableType;

static inline size_t Hash(int key, int a, int b, int p, size_t storageLen);

static inline bool IsCorrectHashFirstLevel(size_t* distribution, size_t distributionArrLen,
                                           size_t valuesArrSize);

static inline void FillFirstLevel(size_t* distribution, size_t distributionArrLen,
                                  unsigned int* values, size_t valuesArrSize, int a, int b,
                                  int p);

static inline bool CheckHashFirstLevel(size_t* distribution, size_t distributionArrLen,
                                       unsigned int* values, size_t valuesArrSize, int a, int b,
                                       int p);

static inline bool FindHashFirstLevel(HashTableType* table,
                                      size_t* distribution, size_t distributionArrLen,
                                      unsigned int* values, size_t valuesArrSize);

static inline void
HashTableCreateArrays(HashTableType* table, size_t* distribution, size_t distributionArrLen);

static inline bool CheckHashSecondLevel(HashTableElemsArr* arr, int a, int b, int p);

static inline void FillArrays           (HashTableType* table, unsigned int* values, size_t valuesArrSize);
static inline bool FindHashesSecondLevel(HashTableType* table, unsigned int* values, size_t valuesArrSize);
static inline void DistributeValues     (HashTableType* table, unsigned int* values, size_t valuesArrSize);

static inline int RandPrimeNumber();

HashTableElemType HashTableElemCtor()
{
    HashTableElemType elem = {};

    elem.key = 0;
    elem.val = false;

    return elem;
}

void HashTableElemDtor(HashTableElemType* elem)
{
    assert(elem);

    elem->key = 0;
    elem->val = false;
}

HashTableElemType HashTableElemInit(const int key, bool val)
{
    HashTableElemType elem = HashTableElemCtor();

    elem.key = key;
    elem.val = val;

    return elem;
}

HashTableElemType* GetElemByKey(HashTableType* table, int key)
{
    int bucketPos = Hash(key, table->hashFuncA, table->hashFuncB, table->hashFuncP,
                         table->numberOfBuckets);

    int pos = Hash(key, table->buckets[bucketPos].hashFuncA, table->buckets[bucketPos].hashFuncB,
                   table->buckets[bucketPos].hashFuncP, table->buckets[bucketPos].dataCapacity);

    return table->buckets[bucketPos].data + pos;
}

HashTableType* HashTableInit(unsigned int* values, size_t valuesArrSize)
{
    HashTableType* table = (HashTableType*) calloc(1, sizeof(*table));

    assert(table);

    const size_t numberOfBuckets = valuesArrSize;

    size_t* distribution = (size_t*) calloc(numberOfBuckets, sizeof(*distribution));
    assert(distribution);

    table->numberOfBuckets = numberOfBuckets;
    table->buckets = (HashTableElemsArr*) calloc(numberOfBuckets, sizeof(*table->buckets));
    assert(table->buckets);

    bool distributionRes = FindHashFirstLevel(table, distribution, numberOfBuckets,
                                              values, valuesArrSize);

    assert(distributionRes);

    HashTableCreateArrays(table, distribution, numberOfBuckets);

    free(distribution);
    distribution = NULL;

    distributionRes = FindHashesSecondLevel(table, values, valuesArrSize);

    assert(distributionRes);

    DistributeValues(table, values, valuesArrSize);

    return table;
}

bool HashTableGetValue(HashTableType* table, const int key)
{
    assert(table);

    HashTableElemType* elem = GetElemByKey(table, key);

    if (elem == NULL)
        return false;

    return elem->key == key ? elem->val : false;
}

void HashTableDtor(HashTableType* table)
{
    if (table == NULL)
        return;

    if (table->buckets == NULL)
        return;

    for (size_t i = 0; i < table->numberOfBuckets; ++i)
        free(table->buckets[i].data);

    free(table->buckets);
    free(table);
}

static inline size_t Hash(int key, int a, int b, int p, size_t storageLen)
{
    if (storageLen == 0 || p == 0)
        return 0;

    return (size_t) ((((unsigned long long) a * key + b) % p) % storageLen);
}

static inline bool IsCorrectHashFirstLevel(size_t* distribution, size_t distributionArrLen,
                                           size_t valuesArrSize)
{
    assert(distribution);

    size_t squaresSum = 0;
    for (size_t i = 0; i < distributionArrLen; ++i)
        squaresSum += distribution[i] * distribution[i];

    return squaresSum <= 4 * valuesArrSize;
}

static inline void FillFirstLevel(size_t* distribution, size_t distributionArrLen,
                                  unsigned int* values, size_t valuesArrSize, int a, int b,
                                  int p)
{
    assert(distribution);
    assert(values);

    memset(distribution, 0, distributionArrLen * sizeof(*distribution));

    for (size_t i = 0; i < valuesArrSize; ++i)
        distribution[Hash(values[i], a, b, p, distributionArrLen)]++;
}

static inline bool CheckHashFirstLevel(size_t* distribution, size_t distributionArrLen,
                                       unsigned int* values, size_t valuesArrSize, int a, int b,
                                       int p)
{
    assert(distribution);
    assert(values);

    FillFirstLevel(distribution, distributionArrLen, values, valuesArrSize, a, b, p);

    if (IsCorrectHashFirstLevel(distribution, distributionArrLen, valuesArrSize))
        return true;

    return false;
}

static inline bool FindHashFirstLevel(HashTableType* table,
                                      size_t* distribution, size_t distributionArrLen,
                                      unsigned int* values, size_t valuesArrSize)
{
    assert(table);
    assert(distribution);
    assert(values);

    size_t attemptNumber = 0;
    const size_t maxNumberOfAttempts = 1000;

    for (; attemptNumber < maxNumberOfAttempts; ++attemptNumber)
    {
        int p = RandPrimeNumber();
        int a = rand() % (p - 1) + 1;
        int b = rand() % p;

        if (CheckHashFirstLevel(distribution, distributionArrLen, values, valuesArrSize,
                                a, b, p))
        {
            table->hashFuncA = a;
            table->hashFuncB = b;
            table->hashFuncP = p;

            return true;
        }
    }

    return false;
}

static inline void
HashTableCreateArrays(HashTableType* table, size_t* distribution, size_t distributionArrLen)
{
    assert(table);
    assert(distribution);
    assert(distributionArrLen == table->numberOfBuckets);

    for (size_t i = 0; i < table->numberOfBuckets; ++i)
    {
        table->buckets[i].dataCapacity = distribution[i] * distribution[i];
        table->buckets[i].dataSize = 0;

        if (distribution[i] > 0)
        {
            table->buckets[i].data = (HashTableElemType*) calloc(table->buckets[i].dataCapacity,
                                                                 sizeof(*table->buckets[i].data));

            assert(table->buckets[i].data);
        }

    }
}

static inline void FillArrays(HashTableType* table, unsigned int* values, size_t valuesArrSize)
{
    assert(table);
    assert(values);

    for (size_t i = 0; i < valuesArrSize; ++i)
    {
        size_t pos = Hash(values[i], table->hashFuncA, table->hashFuncB,
                          table->hashFuncP, table->numberOfBuckets);

        assert(table->buckets[pos].dataSize < table->buckets[pos].dataCapacity);

        table->buckets[pos].data[table->buckets[pos].dataSize++].key = values[i];
    }
}

static inline bool CheckHashSecondLevel(HashTableElemsArr* arr, int a, int b, int p)
{
    assert(arr);

    size_t* distribution = (size_t*) calloc(arr->dataCapacity, sizeof(*distribution));
    assert(distribution);

    for (size_t i = 0; i < arr->dataSize; ++i)
    {
        size_t pos = Hash(arr->data[i].key, a, b, p, arr->dataCapacity);
        distribution[pos]++;

        if (distribution[pos] > 1)
        {
            free(distribution);

            return false;
        }
    }

    free(distribution);

    return true;
}

static inline bool FindHashesSecondLevel(HashTableType* table, unsigned int* values, size_t valuesArrSize)
{
    assert(table);
    assert(values);

    FillArrays(table, values, valuesArrSize);

    const size_t maxNumberOfAttempts = 1000;

    for (size_t i = 0; i < table->numberOfBuckets; ++i)
    {
        if (table->buckets[i].dataCapacity == 0)
            continue;

        size_t attempt = 0;
        for (; attempt < maxNumberOfAttempts; ++attempt)
        {
            int p = RandPrimeNumber();
            int a = rand() % (p - 1) + 1;
            int b = rand() % p;

            if (CheckHashSecondLevel(&table->buckets[i], a, b, p))
            {
                table->buckets[i].hashFuncA = a;
                table->buckets[i].hashFuncB = b;
                table->buckets[i].hashFuncP = p;

                break;
            }
        }

        if (attempt == maxNumberOfAttempts)
        {
            fprintf(stderr, "i - %zu\n", i);
            return false;
        }
    }

    return true;
}

static inline void DistributeValues(HashTableType* table, unsigned int* values, size_t valuesArrSize)
{
    assert(table);
    assert(values);

    for (size_t i = 0; i < valuesArrSize; ++i)
    {
        HashTableElemType* elem = GetElemByKey(table, values[i]);

        assert(elem);

        assert(elem->val == false);

        elem->key = values[i];
        elem->val = true;
    }
}

static inline int RandPrimeNumber()
{
    static int primes[] = 
    {
        (int)1e9 + 7, (int)1e9 + 9, (int)1e9 + 19, (int)1e9 + 21, (int)1e9 + 33,
        (int)1e9 + 87, (int)1e9 + 93, (int)1e9 + 97, (int)1e9 + 103, (int)1e9 + 123,
    };

    static const size_t primesArrSize = sizeof(primes) / sizeof(*primes);

    return primes[rand() % primesArrSize];
}

void ProcessHashTableQueries()
{
    srand(clock());

    size_t n = 0;

    scanf("%zu", &n);

    int* values = (int*) calloc(n, sizeof(*values));
    assert(values);

    for (size_t i = 0; i < n; ++i)
        scanf("%d", values + i);

    HashTableType* hashMap = HashTableInit(values, n);

    int val = 0;
    
    while (scanf("%d", &val) == 1)
    {
        if (HashTableGetValue(hashMap, val))
            printf("YES\n");
        else
            printf("NO\n");
    }

    HashTableDtor(hashMap);
    free(values);
}

int main()
{
    ProcessHashTableQueries();
}