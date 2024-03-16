#include <math.h>

#include "IntroSort.h"
#include "QuadraticSorts.h"
#include "HeapSort.h"
#include "Qsorts.h"

static void IntroSortCall(int* arr, const size_t left, const size_t right, 
                                                                            size_t depth);

static size_t Partition(int* arr, size_t left, size_t right);

static inline void Swap(int* val1, int* val2);

void IntroSortTestConstant(int* arr, const size_t arrSize, double recursionDepthConstant)
{
    size_t depth = (size_t)(log2((double)arrSize) * recursionDepthConstant);

    IntroSortCall(arr, 0, arrSize - 1, depth);
}

void IntroSort(int* arr, const size_t arrSize)
{
    static const size_t optimalDepth = 30;
    size_t depth = (size_t)(log2((double)arrSize) * optimalDepth);

    IntroSortCall(arr, 0, arrSize - 1, depth);
}

static void IntroSortCall(int* arr, const size_t left, const size_t right, 
                                                                            size_t depth)
{
    static const size_t optimalBlockSize = 64;
    static const size_t optimalHeapRank  = 6;
    size_t arrSize = right - left + 1;

    if (left >= right)
        return;
    
    if (arrSize <= optimalBlockSize)
    {
        ShellSort(arr + left, arrSize);
        return;
    }

    if (depth == 0)
    {
        HeapSort(arr + left, arrSize, optimalHeapRank);
        return;
    }

    size_t middle = Partition(arr, left, right);

    IntroSortCall(arr, left,      middle, depth - 1);
    IntroSortCall(arr, middle + 1, right, depth - 1);
}

static size_t Partition(int* arr, size_t left, size_t right)
{
    int pivot = arr[(left + right) >> 1];

    while (left <= right)
    {
        while (arr[left]  < pivot)  ++left;
        while (arr[right] > pivot) --right;

        if (right <= left)
            return right;

        Swap(arr + left, arr + right);
        --right;
        ++left;
    }

    return right;    
}

static inline void Swap(int* val1, int* val2)
{
    int tmp = *val1;

    *val1 = *val2;
    *val2 = tmp;
}
