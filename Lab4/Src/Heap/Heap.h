#ifndef HEAP_H
#define HEAP_H

#include <stddef.h>
#include <stdbool.h>

typedef struct Heap
{
    int*   heapData;
    
    size_t heapCapacity;
    size_t dataEndPos;
} Heap;

Heap  HeapCtor          (int* arr, size_t arrSize);
Heap  HeapBuild         (int* arr, size_t arrSize);
Heap* HeapDtor          (Heap* heap);
void  HeapInsertNextVal (Heap* heap);
int   HeapExtractMax    (Heap* heap);

bool HeapIsValid(Heap* heap);

size_t HeapGetLeftSonPos (size_t valPos);
size_t HeapGetRightSonPos(size_t valPos);

#endif