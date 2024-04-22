#include <assert.h>

#include "HeapSort.h"
#include "Heap/Heap.h"

void HeapSortLinearBuild(int* arr, size_t arrSize)
{
    assert(arr);

    Heap heap = HeapBuild(arr, arrSize);

    HeapDtor(&heap);
}

void HeapSortInserts(int* arr, size_t arrSize)
{
    assert(arr);

    Heap heap = HeapCtor(arr, arrSize);

    for (size_t i = 0; i < arrSize; ++i)
        HeapInsertNextVal(&heap);

    HeapDtor(&heap);
}
