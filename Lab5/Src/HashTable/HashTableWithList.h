#ifdef LIST_TABLE

#ifndef HASH_TABLE_WITH_LIST_H
#define HASH_TABLE_WITH_LIST_H

#include <stddef.h>

#include "HashTable/HashTableList/HashTableList.h"
#include "Hash/Hash.h"

typedef struct
{
    List* buckets; // array of lists
    size_t numberOfBuckets;

    size_t numberOfElementsInserted;

    HashFuncType HashFunc;
} HashTableType;

HashTableType* HashTableCtor(size_t capacity, HashFuncType HashFunc);

void HashTableDtor(HashTableType* table);

void HashTableInsert    (HashTableType* table, const int key);
void HashTableErase     (HashTableType* table, const int key);
bool HashTableGetValue  (HashTableType* table, const int key);

#endif

#endif