#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dynamicArr.h"

static size_t ArrayGetDataIndex(Array* arr, size_t index);
static Array* ArraySizeIncrease(Array* arr);
static Array* ArraySizeDecrease(Array* arr);

Array  ArrayCtor()
{
    Array arr = {};

    arr.data     = NULL;
    arr.capacity = 0;
    arr.size     = 0;
    arr.elemSize = 0;

    return arr;
}

Array  ArrayInit(size_t size, size_t elemSize)
{
    Array arr = {};

    arr.capacity = size;
    arr.size     = 0;
    arr.elemSize = elemSize;

    arr.data = calloc(size, elemSize);

    return arr;
}

Array* ArrayDtor(Array* arr)
{
    arr->size     = 0;
    arr->capacity = 0;
    arr->elemSize = 0;

    free(arr->data);
    arr->data = NULL;

    return NULL;
}

int ArrayPushBack(Array* arr, void* val)
{
    assert(arr->size <= arr->capacity);

    if (arr->size == arr->capacity)
        if (ArraySizeIncrease(arr) == NULL) 
            return 0;

    ArraySetVal(arr, arr->size, val);

    arr->size++;

    return 1;
}

int ArrayPopBack (Array* arr)
{
    if (arr->size * 4 <= arr->capacity)
        arr = ArraySizeDecrease(arr);
    
    if (arr->size == 0)
        return 0;
    
    arr->size--;

    return 1;
}

void* ArrayGetVal(Array* arr, size_t index)
{
    assert(index < arr->size);

    return arr->data + ArrayGetDataIndex(arr, index);
}

Array* ArraySetVal(Array* arr, size_t index, void* val)
{
    assert(index < arr->capacity);

    memcpy(ArrayGetVal(arr, index), val, arr->elemSize);

    return arr;
}

static size_t ArrayGetDataIndex(Array* arr, size_t index)
{
    assert(index < arr->size);
    
    return index * arr->elemSize;
}

static Array* ArraySizeIncrease(Array* arr)
{
    assert(arr->size == arr->capacity);

    arr->capacity *= 2;

    void* tmp = realloc(arr, arr->capacity * arr->elemSize);

    if (tmp != NULL)
        arr->data = tmp;

    return tmp;
}

static Array* ArraySizeDecrease(Array* arr)
{
    assert(arr->size * 4 <= arr->capacity);

    arr->capacity /= 2;

    arr->data = realloc(arr, arr->capacity * arr->elemSize);

    return arr;
}
