#ifdef OPEN_TABLE

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "HashTableOpen.h"

static inline size_t GetPower2Capacity(size_t capacity);

static HashTableElem* HashTableFindElemPlace(HashTableType* table, const int key);

static inline size_t LinearProbeFirstStep   (int key, HashFuncType HashFunc, size_t hashTableSize);
static inline size_t QuadraticProbeFirstStep(int key, HashFuncType HashFunc, size_t hashTableSize);
static inline size_t HashProbeFirstStep     (int key, HashFuncType HashFunc, size_t hashTableSize, 
                                             size_t* secondHashRes);

static inline size_t LinearProbeNextStep    (size_t prevVal, size_t hashTableSize);
static inline size_t QuadraticProbeNextStep (size_t prevVal, size_t hashTableSize,
                                             size_t attemptId);
static inline size_t HashProbeNextStep      (size_t prevVal, size_t hashTableSize, 
                                             size_t secondHashRes);

static inline bool HashTableNeedIncreasing(HashTableType* table);
static void        HashTableIncreaseSize  (HashTableType* table);

static void HashTableDataMoveElem(HashTableType* newTable, HashTableElem* elem);

HashTableElem HashTableElemCtor()
{
    HashTableElem elem = 
    {
        .key   = 0,
        .value = false,

        .isDel = false,
    };

    return elem;
}

HashTableElem HashTableElemInit(int key)
{
    HashTableElem elem = 
    {
        .key = key,
        .value = true,

        .isDel = false,
    };

    return elem;
}

void HashTableElemDtor(HashTableElem* elem)
{
    assert(elem);

    elem->isDel = false;
    elem->key   = 0;
    elem->value = 0;
}

HashTableType* HashTableCtor(size_t capacity, HashFuncType HashFunc, float loadFactor)
{
    HashTableType *table = (HashTableType *) calloc(1, sizeof(*table));
    assert(table);

    table->HashFunc   = HashFunc;
    table->loadFactor = loadFactor;

    table->dataCapacity = GetPower2Capacity(capacity);
    table->data = (HashTableElem*)calloc(table->dataCapacity, sizeof(*table->data));
    assert(table->data);

    table->dataDelSize  = 0;
    table->dataSize     = 0;

    for (size_t i = 0; i < capacity; ++i)
        table->data[i] = HashTableElemCtor();

    return table;
}

void HashTableDtor(HashTableType* table)
{
    assert(table);

    free(table->data);

    table->data         = NULL;
    table->dataCapacity = 0;
    table->dataSize     = 0;
    table->dataDelSize  = 0;
    table->HashFunc     = NULL;

    free(table);
}

void HashTableInsert(HashTableType* table, const int key)
{
    assert(table);

    if (HashTableNeedIncreasing(table))
        HashTableIncreaseSize(table);

    HashTableElem* elem = HashTableFindElemPlace(table, key);
    assert(elem);
    assert(elem->isDel == false);
    
    if (elem->value == true)
        return;

    *elem = HashTableElemInit(key);

    table->dataSize++;

    return;
}

void HashTableErase     (HashTableType* table, const int key)
{
    assert(table);

    HashTableElem* elem = HashTableFindElemPlace(table, key);
    assert(elem);
    assert(elem->isDel == false);
    
    if (elem->value == false)
        return;

    elem->isDel = true;
    elem->value = false;

    table->dataDelSize++;

    return;
}

bool HashTableGetValue  (HashTableType* table, const int key)
{
    assert(table);

    HashTableElem* elem = HashTableFindElemPlace(table, key);
    assert(elem);
    assert(elem->isDel == false);
    
    return elem->value;
}

static HashTableElem* HashTableFindElemPlace(HashTableType* table, const int key)
{
    assert(table);

    size_t attempt = 0;

    size_t probePos = 0;
#if PROBE_FUNC == LINEAR
    probePos = LinearProbeFirstStep(key, table->HashFunc, table->dataCapacity);
#elif PROBE_FUNC == QUADRATIC
    probePos = QuadraticProbeFirstStep(key, table->HashFunc, table->dataCapacity);
#else
    size_t secondHashRes = 0;
    probePos = HashProbeFirstStep(key, table->HashFunc, table->dataCapacity, &secondHashRes);
#endif

    for (attempt = 0; attempt < table->dataCapacity; ++attempt)
    {
        assert(probePos < table->dataCapacity);

        if (!table->data[probePos].isDel && 
            (table->data[probePos].key == key || table->data[probePos].value == false))
            return table->data + probePos;

    #if PROBE_FUNC == LINEAR
        probePos = LinearProbeNextStep(probePos, table->dataCapacity);
    #elif PROBE_FUNC == QUADRATIC
        probePos = QuadraticProbeNextStep(probePos, table->dataCapacity, attempt);
    #else
        probePos = HashProbeNextStep(probePos, table->dataCapacity, secondHashRes);
    #endif
    }

    assert(false);

    return NULL;
}

static inline size_t LinearProbeFirstStep   (int key, HashFuncType HashFunc, size_t hashTableSize)
{
    return HashFunc(key) & (hashTableSize - 1);
}

static inline size_t QuadraticProbeFirstStep(int key, HashFuncType HashFunc, size_t hashTableSize)
{
    return HashFunc(key) & (hashTableSize - 1);
}

static inline size_t HashProbeFirstStep     (int key, HashFuncType HashFunc, size_t hashTableSize, 
                                             size_t* secondHashRes)
{
    assert(secondHashRes);

    const size_t a   = 228;
    const size_t b   = 7777;
    const size_t mod = 1000003;

    size_t secondHash = KnuthHash((unsigned int)key, a, b, mod);

    if (secondHash % 2 == 0)
        ++secondHash;

    secondHash &= (hashTableSize - 1);

    *secondHashRes = secondHash ;

    return HashFunc(key) & (hashTableSize - 1);
}

static inline size_t LinearProbeNextStep    (size_t prevVal, size_t hashTableSize)
{
    return (prevVal + 1) & (hashTableSize - 1);
}

static inline size_t QuadraticProbeNextStep (size_t prevVal, size_t hashTableSize, size_t attemptId)
{
    // assuming c1 = c2 = 1/2 (src : https://en.wikipedia.org/wiki/Quadratic_probing) 
    return (prevVal + attemptId + 1) & (hashTableSize - 1);
}

static inline size_t HashProbeNextStep      (size_t prevVal, size_t hashTableSize, 
                                             size_t secondHashRes)
{
    return (prevVal + secondHashRes) & (hashTableSize - 1);
}

static inline size_t GetPower2Capacity(size_t capacity)
{
    for (size_t size = 2; size < SIZE_MAX; size *= 2)
    {
        if (size >= capacity)
            return size;
    }

    return capacity;
}

static inline bool HashTableNeedIncreasing(HashTableType* table)
{
    assert(table);

    return table->dataDelSize + table->dataSize >= table->dataCapacity * table->loadFactor;
}

static void HashTableIncreaseSize(HashTableType* table)
{
    assert(table);

    static const size_t increaseCoeff = 2;
    size_t newCapacity = table->dataCapacity * increaseCoeff;

    HashTableType* tmpTable = HashTableCtor(newCapacity, table->HashFunc, table->loadFactor);
    for (size_t i = 0; i < table->dataCapacity; ++i)
    {
        if (table->data[i].isDel)
            HashTableElemDtor(table->data + i);
        else
            HashTableDataMoveElem(tmpTable, table->data + i);
    }

    free(table->data);
    table->data         = tmpTable->data;
    table->dataCapacity = tmpTable->dataCapacity;
    table->dataDelSize  = 0;

    free(tmpTable);
}

static void HashTableDataMoveElem(HashTableType* newTable, HashTableElem* elem)
{
    assert(newTable);
    assert(elem);

    HashTableElem* elemToChange = HashTableFindElemPlace(newTable, elem->key);

    if (elemToChange->key == elem->key)
        return;

    assert(elem->value == true);
    assert(elem->isDel == false);
    assert(elemToChange->value == false);
    assert(elemToChange->isDel == false);

    elemToChange->key   = elem->key;
    elemToChange->value = elem->value;
    elemToChange->isDel = elem->isDel;
}

#endif