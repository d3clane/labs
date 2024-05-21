#ifdef IDEAL_TABLE

#ifndef HASH_TABLE_IDEAL_H
#define HASH_TABLE_IDEAL_H

typedef struct
{
    int key;

    bool val;
} HashTableElemType;

// using universal hash (Ax + B) % P - A, B, P - constants
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

HashTableElemType HashTableElemCtor();
void HashTableElemDtor(HashTableElemType* elem);
HashTableElemType HashTableElemInit(const int key, bool val);

HashTableElemType* GetElemByKey(HashTableType* table, int key);
HashTableType* HashTableInit(unsigned int* values, size_t valuesArrSize);
bool HashTableGetValue(HashTableType* table, const int key);
void HashTableDtor(HashTableType* table);

#endif

#endif