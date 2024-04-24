#ifdef LIST_TABLE

#include <assert.h>
#include <stdio.h>
#include <stdbool.h>

#include "HashTableWithList.h"

static inline size_t
BucketsGetBucketPos(HashFuncType HashFunc, const size_t numberOfBuckets, int key);

static inline size_t HashTableGetBucketPos(HashTableType *table, const int key);

static inline size_t GetPrimeCapacity(size_t capacity)
{
    static const size_t hashTablePrimes[] =
            {
                    53, 97, 193, 389, 769, 1543, 3079, 6151, 12289, 24593, 49157, 98317,
                    196613, 393241, 786433, 1572869, 3145739, 6291469, 12582917, 25165843,
                    50331653, 100663319, 201326611, 402653189, 805306457, 1610612741
            };

    static const size_t hashTablePrimesArrSize = sizeof(hashTablePrimes) / sizeof(*hashTablePrimes);

    for (size_t i = 0; i < hashTablePrimesArrSize; ++i)
    {
        if (hashTablePrimes[i] >= capacity)
            return hashTablePrimes[i];
    }

    return capacity;
}

void HashTableDtor(HashTableType *table)
{
    assert(table);

    if (table->buckets)
    {
        for (size_t i = 0; i < table->numberOfBuckets; ++i)
            ListDtor(table->buckets + i);

        free(table->buckets);
    }

    table->buckets = NULL;
    table->numberOfBuckets = 0;
    table->HashFunc = NULL;

    free(table);
}

HashTableType *HashTableCtor(size_t capacity, HashFuncType HashFunc, float loadFactor)
{
    HashTableType *table = (HashTableType *) calloc(1, sizeof(*table));
    assert(table);

    table->HashFunc   = HashFunc;
    table->loadFactor = loadFactor;

    table->numberOfBuckets = GetPrimeCapacity(capacity);

    table->buckets = (List*) calloc(table->numberOfBuckets, sizeof(*table->buckets));
    assert(table->buckets);

    for (size_t i = 0; i < table->numberOfBuckets; ++i)
        table->buckets[i] = ListCtor();

    return table;
}

static inline bool HashTableNeedIncreasing(HashTableType *table)
{
    return (float) table->numberOfElementsInserted >
           table->loadFactor * (float) table->numberOfBuckets;
}

static void HashTableCapacityIncrease(HashTableType *table)
{
    assert(table);

    static const size_t increasingCoeff = 2;

    size_t newCap = GetPrimeCapacity(table->numberOfBuckets * increasingCoeff);

    List* tmpBuckets = (List*) calloc(newCap, sizeof(*table->buckets));
    assert(tmpBuckets);
    for (size_t i = 0; i < newCap; ++i)
        tmpBuckets[i] = ListCtor();

    for (size_t i = 0; i < table->numberOfBuckets; ++i)
    {
        assert(table->buckets[i].begin);

        ListElem* elem = table->buckets[i].begin->nextElem;
        
        while (elem != table->buckets[i].begin)
        {
            int val = ListGetKey(elem);

            size_t bucketPos = BucketsGetBucketPos(table->HashFunc, newCap, elem->key);
            ListInsert(tmpBuckets + bucketPos, tmpBuckets[bucketPos].begin, val);

            elem = elem->nextElem;
        }
        
        ListDtor(table->buckets + i);
    }

    free(table->buckets);

    table->buckets         = tmpBuckets;
    table->numberOfBuckets = newCap;
}

void HashTableInsert(HashTableType *table, const int key)
{
    assert(table);

    size_t bucketPos = HashTableGetBucketPos(table, key);

    ListInsert(table->buckets + bucketPos, table->buckets[bucketPos].begin, key);

    table->numberOfElementsInserted++;

    if (HashTableNeedIncreasing(table))
        HashTableCapacityIncrease(table);
}

void HashTableErase(HashTableType *table, const int key)
{
    assert(table);

    size_t bucketPos = HashTableGetBucketPos(table, key);
    ListErase(table->buckets + bucketPos, key);

    table->numberOfElementsInserted--;
}

bool HashTableGetValue(HashTableType *table, const int key)
{
    assert(table);

    size_t bucketPos = HashTableGetBucketPos(table, key);

    ListElem* elem = ListFindKey(table->buckets + bucketPos, key);

    return elem ? true : false;
}

static inline size_t
BucketsGetBucketPos(HashFuncType HashFunc, size_t numberOfBuckets, const int key)
{
    return (size_t) HashFunc(key) % numberOfBuckets;
}

static inline size_t HashTableGetBucketPos(HashTableType *table, const int key)
{
    return BucketsGetBucketPos(table->HashFunc, table->numberOfBuckets, key);
}

#endif