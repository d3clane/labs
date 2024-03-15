#include "Qsorts.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static inline void Swap(int* val1, int* val2);

static void QsortHoareCall      (int* arr, const size_t left, const size_t right);
static void QsortLomutoCall     (int* arr, const size_t left, const size_t right);
static void QsortTernaryCall    (int* arr, const size_t left, const size_t right);
static void QsortOneBranchCall  (int* arr, const size_t left, const size_t right);

static size_t PartitionHoare  (int* arr, size_t left, size_t right);
static size_t PartitionLomuto (int* arr, size_t left, size_t right);
static void   PartitionTernary(int* arr, size_t left, size_t right, 
                                         size_t* equalPartBeginPos, size_t* equalPartEndPos);

void QsortHoare  (int* arr, const size_t arrSize)
{
    if (arrSize == 0)
        return;

    QsortHoareCall(arr, 0, arrSize - 1);
}

void QsortLomuto (int* arr, const size_t arrSize)
{
    if (arrSize == 0)
        return;

    QsortLomutoCall(arr, 0, arrSize - 1);
}

void QsortTernary(int* arr, const size_t arrSize)
{
    if (arrSize == 0)
        return;

    QsortTernaryCall(arr, 0, arrSize - 1);
}

void QsortOneBranch(int* arr, const size_t arrSize)
{
    if (arrSize == 0)
        return;
    
    QsortOneBranchCall(arr, 0, arrSize - 1);
}

static void QsortHoareCall (int* arr, const size_t left, const size_t right)
{
    if (left >= right)
        return;

    size_t mid = PartitionHoare(arr, left, right);

    QsortHoareCall(arr, left, mid);
    QsortHoareCall(arr, mid + 1, right);
}

static void QsortLomutoCall(int* arr, const size_t left, const size_t right)
{
    if (left >= right)
        return;

    size_t mid = PartitionLomuto(arr, left, right);

    QsortLomutoCall(arr, left, mid);
    QsortLomutoCall(arr, mid + 1, right);    
}

static void QsortOneBranchCall  (int* arr, const size_t leftPos, const size_t rightPos)
{
    if (leftPos >= rightPos)
        return;
    
    size_t left  = leftPos;
    size_t right = rightPos;

    do
    {
        size_t mid = PartitionHoare(arr, left, right);
        if (mid - left + 1 > right - mid) // mid - left > right - mid - 1
        {
            QsortOneBranchCall(arr, mid + 1, right);

            right = mid;
        }
        else
        {
            QsortOneBranchCall(arr, left, mid);

            left = mid + 1;
        }
    } while (left < right);
}

static void QsortTernaryCall(int* arr, const size_t left, const size_t right)
{
    if (left >= right)
        return;

    size_t firstSegmentEnd    = 0;
    size_t secondSegmentBegin = 0;

    PartitionTernary(arr, left, right, &firstSegmentEnd, &secondSegmentBegin);

    if (firstSegmentEnd != 0)
        QsortTernaryCall(arr, left, firstSegmentEnd - 1);
    
    QsortTernaryCall(arr, secondSegmentBegin + 1, right);
}

static size_t PartitionHoare (int* arr,       size_t left,       size_t right)
{
    int pivot = arr[(left + right) >> 1];

    while (left <= right)
    {
        while (arr[left]  < pivot)  ++left;
        while (arr[right] >  pivot) --right;

        if (right <= left)
            return right;

        Swap(arr + left, arr + right);
        --right;
        ++left;
    }

    return right;
}

static size_t PartitionLomuto(int* arr,       size_t left,       size_t right)
{
    size_t pivotPos = (left + right) >> 1;
    int pivot = arr[pivotPos];
    Swap(arr + right, arr + pivotPos);
    size_t leftBounder = left;
    size_t currElement = left;

    while (currElement <= right)
    {
        if (arr[currElement] < pivot)
        {
            Swap(arr + currElement, arr + leftBounder);
            ++leftBounder;
        }
        ++currElement;
    }
    
    Swap(arr + leftBounder, arr + right);

    return leftBounder;
}

static void   PartitionTernary(int* arr, size_t left, size_t right, 
                                         size_t* equalPartBeginPos, size_t* equalPartEndPos)
{
    int pivot = arr[(left + right) >> 1];
    
    size_t middle = left;
    while (middle <= right)
    {
        if (arr[middle] < pivot)
        {
            Swap(arr + left, arr + middle);
            ++left;
            ++middle;
        } 
        else if (arr[middle] == pivot)
        {
            ++middle;
        }
        else 
        {
            Swap(arr + middle, arr + right);
            --right;
        }
    }

    *equalPartBeginPos = left;
    *equalPartEndPos   = right;
}

static inline void Swap(int* val1, int* val2)
{
    int temp = *val1;
               *val1 = *val2;
                       *val2 = temp;
}
