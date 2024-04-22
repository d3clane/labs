#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Heap.h"

#define NO_NODE_FOUND -1

static void HeapSiftUp  (Heap* heap, size_t valPos);
static void HeapSiftDown(Heap* heap, size_t valPos);

static inline int HeapGetFatherPos(const Heap* heap, size_t valPos);
static inline int HeapGetMaxSonPos(const Heap* heap, size_t valPos);

static inline void   Swap(int*   val1, int*   val2);
static inline size_t Min (size_t val1, size_t val2);

Heap  HeapCtor(int* arr, size_t arrSize)
{
    Heap heap =
    {
        .heapData = arr,

        .heapCapacity = arrSize,
        .dataEndPos  = 0,
    };

    return heap;
}

Heap HeapBuild(int* arr, size_t arrSize)
{
    assert(arr);

    Heap heap       = HeapCtor(arr, arrSize);
    heap.dataEndPos = arrSize;

    const size_t heapRank = 2;

    for (size_t i = arrSize / heapRank; i + 1 > 0; --i)
        HeapSiftDown(&heap, i);

    return heap;
}

Heap* HeapDtor(Heap* heap)
{
    assert(heap);

    heap->heapData = NULL;
    heap->dataEndPos  = 0;

    return NULL;
}

int HeapExtractMax  (Heap* heap)
{
    assert(heap);
    assert(heap->heapData);

    int maxVal = heap->heapData[0];
    heap->dataEndPos--;

    heap->heapData[0] = heap->heapData[heap->dataEndPos];

    HeapSiftDown(heap, 0);

    return maxVal;
}

void  HeapInsertNextVal(Heap* heap)
{
    assert(heap);
    assert(heap->dataEndPos < heap->heapCapacity);

    HeapSiftUp(heap, heap->dataEndPos++);
}

static void HeapSiftUp  (Heap* heap, size_t valPos)
{
    assert(heap);

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

static inline int HeapGetFatherPos(const Heap* heap, size_t valPos)
{
    assert(heap);

    if (valPos == 0)
        return NO_NODE_FOUND;

    return (int)((valPos - 1) / 2);
}

size_t HeapGetLeftSonPos(size_t valPos)
{
    return valPos * 2 + 1;
}

size_t HeapGetRightSonPos(size_t valPos)
{
    return valPos * 2 + 2;
}

static inline int HeapGetMaxSonPos(const Heap* heap, size_t valPos)
{
    assert(heap);

    size_t leftSonPos    = HeapGetLeftSonPos(valPos);
    size_t rightSonPos   = HeapGetRightSonPos(valPos);

    if (leftSonPos >= heap->dataEndPos)
        return -1;

    if (rightSonPos >= heap->dataEndPos)
        return (int)leftSonPos;

    if (heap->heapData[leftSonPos] >= heap->heapData[rightSonPos])
        return (int)leftSonPos;
    
    return (int)rightSonPos;
}

bool HeapIsValid(Heap* heap)
{
    assert(heap);
    assert(heap->heapData);

    for (size_t i = 1; i < heap->dataEndPos; ++i)
    {
        int fatherPos = HeapGetFatherPos(heap, i);
        assert(0 <= fatherPos && fatherPos < heap->dataEndPos);

        if (heap->heapData[HeapGetFatherPos(heap, i)] < heap->heapData[i])
            return false;
    }

    return true;
}

static inline void Swap(int* val1, int* val2)
{
    assert(val1);
    assert(val2);
    
    int tmp = *val1;
    *val1 = *val2;
    *val2 = tmp;
}

static inline size_t  Min (size_t  val1, size_t  val2)
{
    return val1 < val2 ? val1 : val2;
}