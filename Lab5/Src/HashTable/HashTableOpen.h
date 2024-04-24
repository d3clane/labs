#ifdef OPEN_TABLE

#ifndef HASH_TABLE_OPEN_H
#define HASH_TABLE_OPEN_H

#include <stddef.h>
#include <stdbool.h>

#include "HashTable/HashTableList/HashTableList.h"
#include "Hash/Hash.h"

typedef struct 
{
    int key;

    bool value;

    bool isDel;
} HashTableElem;

typedef struct
{
    HashTableElem* data;
    size_t dataCapacity; // always power of 2
    size_t dataSize;
    size_t dataDelSize;

    HashFuncType  HashFunc;
} HashTableType;

HashTableType* HashTableCtor(size_t capacity, HashFuncType HashFunc);

void HashTableDtor(HashTableType* table);

void HashTableInsert(HashTableType* table, const int key);
void HashTableErase     (HashTableType* table, const int key);
bool HashTableGetValue  (HashTableType* table, const int key);

HashTableElem HashTableElemCtor();
HashTableElem HashTableElemInit(int key);
void          HashTableElemDtor(HashTableElem* elem);

#endif

#endif