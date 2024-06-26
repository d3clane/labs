#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Common/Common.h"
#include "Heap.h"

#define NO_NODE_FOUND -1

static void HeapSiftDown(Heap* heap, size_t valPos);

static inline int HeapGetMaxSonPos(const Heap* heap, size_t valPos);

static inline size_t Min (size_t val1, size_t val2);

Heap HeapCtor(size_t heapSize, size_t heapRank)
{
    Heap heap =
    {
        .heapData = (int*)calloc(heapSize, sizeof(int)),
        
        .heapCapacity = heapSize,
        .dataEndPos  = 0,

        .heapRank = heapRank,
    };

    assert(heap.heapData);
    
    return heap;
}

Heap HeapBuild(int* arr, size_t arrSize, size_t heapRank)
{
    assert(arr);

    Heap heap       = 
    {
        .heapData = arr,

        .heapCapacity = arrSize,
        .dataEndPos   = arrSize,
        
        .heapRank     = heapRank,
    };

    for (size_t i = arrSize / heapRank; i + 1 > 0; --i)
        HeapSiftDown(&heap, i);

    return heap;
}

Heap* HeapDtor(Heap* heap)
{
    assert(heap);

    if (heap->heapData != NULL)
        free(heap->heapData);

    heap->heapData = NULL;
    heap->dataEndPos  = 0;
    heap->heapRank    = 0;

    return NULL;
}

int HeapExtractMax  (Heap* heap)
{
    assert(heap);
    assert(heap->heapCapacity >= 1);
    assert(heap->heapData);

    int maxVal = heap->heapData[0];
    
    heap->dataEndPos--;

    heap->heapData[0] = heap->heapData[heap->dataEndPos];

    HeapSiftDown(heap, 0);

    return maxVal;
}

static void HeapSiftDown(Heap* heap, size_t valPos)
{
    assert(heap);

    size_t curPos = valPos;

    int maxChildPos = HeapGetMaxSonPos(heap, curPos);
    while (maxChildPos != NO_NODE_FOUND && heap->heapData[curPos] < heap->heapData[maxChildPos])
    {
        Swap(&heap->heapData[curPos], &heap->heapData[maxChildPos]);

        curPos      = (size_t)maxChildPos;
        maxChildPos = HeapGetMaxSonPos(heap, curPos);
    }
}

static inline int HeapGetMaxSonPos(const Heap* heap, size_t valPos)
{
    assert(heap);

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

static inline size_t  Min (size_t val1, size_t val2)
{
    return val1 < val2 ? val1 : val2;
}
