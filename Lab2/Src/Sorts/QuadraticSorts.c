#include "QuadraticSorts.h"

static inline void Swap(int* val1, int* val2);

void BubbleSort   (int* arr, const size_t arrSize)
{
    if (arrSize == 0)
        return;

    for (size_t i = 0; i < arrSize - 1; ++i)
    {
        for (size_t j = 0; j < arrSize - 1; ++j)
        {
            if (arr[j] > arr[j + 1])
                Swap(&arr[j], &arr[j + 1]);
        }
    }
}

void InsertionSort(int* arr, const size_t arrSize)
{
    for (size_t i = 1; i < arrSize; ++i)
    {
        // chosen element - arr[i]. Move it to the correct pos
        size_t j = i;
        int valueToMove = arr[j];

        while (j > 0 && arr[j - 1] > valueToMove)
        {
            arr[j] = arr[j - 1];
            --j;
        }
        arr[j] = valueToMove;
    }
}

void SelectionSort(int* arr, const size_t arrSize)
{
    for (size_t i = 0; i < arrSize; ++i)
    {
        size_t minElementPos = i;
        for (size_t j = i; j < arrSize; ++j)
        {
            if (arr[j] < arr[minElementPos])
                minElementPos = j;
        }

        Swap(&arr[i], &arr[minElementPos]);
    }
}

void ShellSort    (int* arr, const size_t arrSize)
{
    size_t step = 1;
    while (step <= arrSize / 9) step = step * 3 + 1;

    for (; step > 0; step /= 3)
    {
        for (size_t i = step; i < arrSize; i += step)
        {
            size_t j = i;
            int valueToMove = arr[j];

            while (j >= step && arr[j - step] > valueToMove)
            {
                arr[j] = arr[j - step];
                j -= step;
            }
            arr[j] = valueToMove;
        }
    }
}

static inline void Swap(int* val1, int* val2)
{
    int tmp = *val1;
              *val1 = *val2;
                      *val2 = tmp;
}
