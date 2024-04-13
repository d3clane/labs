#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Swap(int* val1, int* val2);
void   QuickSort(int* arr, const size_t left, const size_t right);
size_t Partition(int* arr,       size_t left,       size_t right);

void QuickSort(int* arr, const size_t left, const size_t right)
{
    assert(arr);

    if (left >= right)
        return;

    size_t mid = Partition(arr, left, right);

    QuickSort(arr, left, mid);
    QuickSort(arr, mid + 1, right);
}

size_t Partition(int* arr, size_t left, size_t right)
{
    assert(arr);

    int pivotIndex = rand() % (right - left + 1) + left;
    int pivot      = arr[pivotIndex];

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

void Swap(int* val1, int* val2)
{
    assert(val1);
    assert(val2);
    
    int temp = *val1;
               *val1 = *val2;
                       *val2 = temp;
}

size_t GetInput(int** arr)
{
    assert(arr);

    size_t arrSize = 0;
    int scanfRes = scanf("%zu", &arrSize);
    assert(scanfRes == 1);

	*arr = (int*)calloc(arrSize, sizeof(**arr));
    assert(*arr);

    for (size_t i = 0; i < arrSize; ++i)
    {
        int scanfResult = scanf("%d", arr + i);
        assert(scanfResult == 1);
    }

    return arrSize;
}

void PrintArray(int* arr, size_t arrSize)
{
    for (size_t i = 0; i < arrSize; ++i)
        printf("%d ", arr[i]);
}

int main()
{
    srand(time(NULL));

    int* arr = NULL;
    size_t arrSize = GetInput(&arr);

    QuickSort(arr, 0, arrSize - 1);

    PrintArray(arr, arrSize);
	
	free(arr);
    return 0;
}
