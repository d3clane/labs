#ifndef DYNAMIC_ARR_H
#define DYNAMIC_ARR_H

#include <stddef.h>

typedef struct Array
{
    void* data;
    size_t elemSize;

    size_t size;
    size_t capacity;
} Array;

Array  ArrayCtor();
Array  ArrayInit(size_t size, size_t elemSize);
Array* ArrayDtor(Array* arr);

Array* ArrayPushBack(Array* arr, void* val);
Array* ArrayPopBack (Array* arr);

void*  ArrayGetVal(Array* arr, size_t index);
Array* ArraySetVal(Array* arr, size_t index, void* val);

#endif