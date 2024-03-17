#include <assert.h>
#include <stdint.h>
#include <string.h>

#include "DigitsSorts.h"

static inline uint8_t GetByte(int value, uint8_t shift);

static void MSDSortCall(int* arr, size_t left, size_t right, size_t byteId, int* tmpResBuffer);

void LSDSort(int* arr, size_t arrSize)
{
    int* tmpRes = (int*) calloc(arrSize, sizeof(*tmpRes));
    assert(tmpRes);
    
#define PREF_CNT_ARR_SIZE 256

    static size_t prefCnt[PREF_CNT_ARR_SIZE] = {};

    for (uint8_t shift = 0; shift < 64; shift += 8)
    {
        memset(prefCnt, 0, sizeof(prefCnt));

        for (size_t i = 0; i < arrSize; ++i)
            prefCnt[GetByte(arr[i], shift)]++;

        for (size_t i = 1; i < PREF_CNT_ARR_SIZE; ++i)
            prefCnt[i] += prefCnt[i - 1];

        for (int i = (int)arrSize - 1; i > -1; --i)
        {
            uint8_t valueByte = GetByte(arr[i], shift);

            tmpRes[prefCnt[valueByte] - 1] = arr[i];
            --prefCnt[valueByte];
        }

        memcpy(arr, tmpRes, arrSize * sizeof(*arr));
    }

#undef PREF_CNT_ARR_SIZE

    free(tmpRes);
    tmpRes = NULL;
}

void MSDSort(int* arr, size_t arrSize)
{
    int* tmpResBuffer = (int*)calloc(arrSize, sizeof(*tmpResBuffer));
    assert(tmpResBuffer);

    MSDSortCall(arr, 0, arrSize, sizeof(int), tmpResBuffer);

    free(tmpResBuffer);
}

static void MSDSortCall(int* arr, size_t left, size_t right, size_t byteId, int* tmpResBuffer)
{
    #define PREF_CNT_ARR_SIZE 256

    if (byteId == 0 || left + 1 >= right)
        return;

    uint8_t shift = (uint8_t)(byteId - 1) * 8;

    size_t prefCnt[PREF_CNT_ARR_SIZE] = {};

    for (size_t i = left; i < right; ++i)
        prefCnt[GetByte(arr[i], shift)]++;

    for (size_t i = 1; i < PREF_CNT_ARR_SIZE; ++i)
        prefCnt[i] += prefCnt[i - 1];

    for (size_t i = left; i < right; ++i)
    {
        uint8_t valueByte = GetByte(arr[i], shift);

        tmpResBuffer[prefCnt[valueByte] - 1] = arr[i];
        --prefCnt[valueByte];
    }

    memcpy(arr + left, tmpResBuffer, (right - left) * sizeof(*arr));

    for (size_t i = 0; i < PREF_CNT_ARR_SIZE - 1; ++i)
        MSDSortCall(arr, left + prefCnt[i], left + prefCnt[i + 1], byteId - 1, tmpResBuffer);

    MSDSortCall(arr, left + prefCnt[PREF_CNT_ARR_SIZE - 1], right, byteId - 1, tmpResBuffer);

    #undef PREF_CNT_ARR_SIZE
}

static inline uint8_t GetByte(int value, uint8_t shift)
{
    assert(value >= 0);
    
    return (uint8_t)((value >> shift) & 0xff);
}
