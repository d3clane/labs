#ifndef QSORTS_H
#define QSORTS_H

#include <stddef.h>

void QsortHoare             (int* arr, const size_t arrSize);
void QsortLomuto            (int* arr, const size_t arrSize);
void QsortTernary           (int* arr, const size_t arrSize);
void QsortOneBranch         (int* arr, const size_t arrSize);
void QsortRndPivot          (int* arr, const size_t arrSize);
void QsortMedian3Pivot      (int* arr, const size_t arrSize);
void QsortMedianRnd3Pivot   (int* arr, const size_t arrSize);

#endif