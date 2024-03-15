#ifndef HEAP_H
#define HEAP_H

#include <stddef.h>

typedef struct Heap
{
    int*     heapData;
    size_t dataEndPos;

    size_t heapRank;
} Heap;

Heap  HeapCtor          (size_t heapSize, size_t heapRank);
Heap  HeapBuild         (int* arr, size_t arrSize, size_t heapRank);
Heap* HeapDtor          (Heap* heap);
void  HeapInsert        (Heap* heap, int val);
int   HeapGetMax        (Heap* heap);
int   HeapExtractMax    (Heap* heap);

#endif