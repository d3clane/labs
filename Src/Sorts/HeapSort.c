#include "HeapSort.h"
#include "Heap/Heap.h"

void HeapSort(int* arr, size_t arrSize, size_t heapRank)
{
    Heap heap = HeapBuild(arr, arrSize, heapRank);

    for (size_t i = arrSize - 1; i + 1 > 0; --i)
        arr[i] = HeapExtractMax(&heap);
}