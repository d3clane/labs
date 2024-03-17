#include <assert.h>
#include <string.h>

#include "MergeSorts.h"

static void Merge(const int* src1, size_t src1Size, const int* src2, size_t src2Size, int* tmpBuffer);

static void RecursiveMergeSortCall(int* arr, size_t left, size_t right, int* tmpBuffer);

static inline size_t Min(size_t val1, size_t val2);

void RecursiveMergeSort(int* arr, const size_t arrSize)
{
    int* tmpBuffer = (int*)calloc(arrSize, sizeof(*tmpBuffer));

    RecursiveMergeSortCall(arr, 0, arrSize, tmpBuffer);

    free(tmpBuffer);
}


void IterativeMergeSort(int* arr, const size_t arrSize)
{
    int* tmpBuffer = (int*)calloc(arrSize, sizeof(*tmpBuffer));

    for (size_t blockSz = 1; blockSz < arrSize; blockSz *= 2)
    {
        for (size_t leftBlockPos = 0; leftBlockPos + blockSz < arrSize; leftBlockPos += 2 * blockSz)
        {
            size_t right = leftBlockPos + blockSz;
            size_t rightBlockSize = Min(blockSz, arrSize - right);
            Merge(arr + leftBlockPos, blockSz, arr + right, rightBlockSize, tmpBuffer);
                
            memcpy(arr + leftBlockPos, tmpBuffer, (blockSz + rightBlockSize) * sizeof(*arr));
        }
    }

    free(tmpBuffer);
}

static void RecursiveMergeSortCall(int* arr, size_t left, size_t right, int* tmpBuffer)
{
    if (left + 1 >= right)
        return;

    size_t mid = (left + right) >> 1;

    RecursiveMergeSortCall(arr, left, mid,  tmpBuffer);
    RecursiveMergeSortCall(arr, mid, right, tmpBuffer);

    Merge(arr + left, mid - left, arr + mid, right - mid, tmpBuffer);
    memcpy(arr + left, tmpBuffer, (right - left) * sizeof(*arr));
}

static void Merge(const int* src1, size_t src1Size, const int* src2, size_t src2Size, int* tmpBuffer)
{
    assert(src1);
    assert(src2);
    assert(tmpBuffer);

    size_t src1Pos = 0;
    size_t src2Pos = 0;
    size_t tmpBufferPos = 0;

    while (src1Pos < src1Size && src2Pos < src2Size)
    {
        if (src1[src1Pos] <= src2[src2Pos])
            tmpBuffer[tmpBufferPos++] = src1[src1Pos++];
        else
            tmpBuffer[tmpBufferPos++] = src2[src2Pos++];
    }

    while (src1Pos < src1Size)    
        tmpBuffer[tmpBufferPos++] = src1[src1Pos++];
    
    while (src2Pos < src2Size)
        tmpBuffer[tmpBufferPos++] = src2[src2Pos++];
}

static inline size_t Min(size_t val1, size_t val2)
{
    return val1 < val2 ? val1 : val2;
}
