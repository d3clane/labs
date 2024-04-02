#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Heap.h"

#define NO_NODE_FOUND

static void HeapSiftUp  (Heap* heap, size_t valPos);
static void HeapSiftDown(Heap* heap, size_t valPos);

static inline int HeapGetFatherPos(Heap* heap, size_t valPos);
static inline int HeapGetMaxSonPos(Heap* heap, size_t valPos);

static inline void   Swap(int*   val1, int*   val2);
static inline size_t Min (size_t val1, size_t val2);

Heap HeapCtor(size_t heapSize, size_t heapRank)
{
    Heap heap =
    {
        .heapData = (int*)calloc(heapSize, sizeof(int)),
        .dataEndPos  = 0,

        .heapRank = heapRank,
    };

    assert(heap.heapData);
    
    return heap;
}

Heap HeapBuild(int* arr, size_t arrSize, size_t heapRank)
{
    Heap heap       = HeapCtor(arrSize, heapRank);
    heap.heapData   = arr;
    heap.dataEndPos = arrSize;

    for (size_t i = arrSize / heapRank; i + 1 > 0; --i)
        HeapSiftDown(&heap, i);

    return heap;
}

Heap* HeapDtor(Heap* heap)
{
    if (heap->heapData != NULL)
        free(heap->heapData);

    heap->heapData = NULL;
    heap->dataEndPos  = 0;
    heap->heapRank    = 0;

    return NULL;
}

void  HeapInsert        (Heap* heap, int val)
{
    heap->heapData[heap->dataEndPos++] = val;

    HeapSiftUp(heap, heap->dataEndPos - 1);
}

int HeapGetMax      (Heap* heap)
{
    return heap->heapData[0];
}

int HeapExtractMax  (Heap* heap)
{
    int MaxVal = HeapGetMax(heap);
    heap->dataEndPos--;

    heap->heapData[0] = heap->heapData[heap->dataEndPos];

    HeapSiftDown(heap, 0);

    return MaxVal;
}

static void HeapSiftUp  (Heap* heap, size_t valPos)
{
    size_t curPos = valPos;

    int fatherPos = HeapGetFatherPos(heap, curPos);
    while (fatherPos != NO_NODE_FOUND && heap->heapData[curPos] > heap->heapData[fatherPos])
    {
        Swap(&heap->heapData[curPos], &heap->heapData[fatherPos]);

        curPos    = (size_t)fatherPos;
        fatherPos = HeapGetFatherPos(heap, curPos);
    }
}

static void HeapSiftDown(Heap* heap, size_t valPos)
{
    size_t curPos = valPos;

    int maxChildPos = HeapGetMaxSonPos(heap, curPos);
    while (maxChildPos != NO_NODE_FOUND && heap->heapData[curPos] < heap->heapData[maxChildPos])
    {
        Swap(&heap->heapData[curPos], &heap->heapData[maxChildPos]);

        curPos      = (size_t)maxChildPos;
        maxChildPos = HeapGetMaxSonPos(heap, curPos);
    }
}

static inline int HeapGetFatherPos(Heap* heap, size_t valPos)
{
    if (valPos == 0)
        return NO_NODE_FOUND;

    return (int)((valPos - 1) / heap->heapRank);
}

static inline int HeapGetMaxSonPos(Heap* heap, size_t valPos)
{
    size_t maxSonPos    = valPos * heap->heapRank + 1;
    size_t endSonPos    = Min((valPos + 1) * heap->heapRank + 1, heap->dataEndPos);
    // sons : [maxSonPos, endSonPos)

    if (maxSonPos >= heap->dataEndPos)
        return NO_NODE_FOUND;
    
    for (size_t sonPos = maxSonPos + 1; sonPos < endSonPos; ++sonPos)
    {
        if (heap->heapData[maxSonPos] < heap->heapData[sonPos])
            maxSonPos = sonPos;
    }

    return (int)maxSonPos;
}

static inline void Swap(int* val1, int* val2)
{
    int tmp = *val1;
    *val1 = *val2;
    *val2 = tmp;
}

static inline size_t  Min (size_t  val1, size_t  val2)
{
    return val1 < val2 ? val1 : val2;
}
