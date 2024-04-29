#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Array
{
    int* data;

    size_t size;
    size_t capacity;
} Array;

Array  ArrayCtor ();
Array* ArrayDtor (Array* arr);
Array* ArrayClear(Array* arr);

int    ArrayPushBack(Array* arr, int val);
int    ArrayPopBack (Array* arr);

int    ArrayGetVal(Array* arr, size_t index);
Array* ArraySetVal(Array* arr, size_t index, int val);

static bool ArrayIsEmpty(Array* arr);

static Array* ArraySizeIncrease(Array* arr);
static Array* ArraySizeDecrease(Array* arr);

typedef struct Heap
{
    Array heapData;
} Heap;

typedef enum MinMax
{
    MIN = 0,
    MAX = 1,
} MinMax;

typedef bool (*CompareFunc)(int val1, int val2);

Heap  HeapCtor      ();
Heap* HeapDtor      (Heap* heap);
void  HeapInsert    (Heap* heap, int n, int* error);
int   HeapExtractMin(Heap* heap,        int* error);
int   HeapGetMin    (Heap* heap,        int* error);
int   HeapExtractMax(Heap* heap,        int* error);
int   HeapGetMax    (Heap* heap,        int* error);

size_t   HeapGetSize   (Heap* heap);
void     HeapClear     (Heap* heap);

static void HeapSiftUp     (Heap* heap, size_t valPos, int* error);
static void HeapSiftUpMax  (Heap* heap, size_t valPos, int* error);
static void HeapSiftUpMin  (Heap* heap, size_t valPos, int* error);
static void HeapSiftDown   (Heap* heap, size_t valPos, int* error);
static void HeapSiftDownMax(Heap* heap, size_t valPos, int* error);
static void HeapSiftDownMin(Heap* heap, size_t valPos, int* error);

static int HeapGetFatherPos     (size_t valPos);
static int HeapGetGrandpaPos    (size_t valPos);

static int HeapGetMinMaxSonPos  (Heap* heap, size_t valPos, CompareFunc Compare);
static int HeapGetMinSonPos     (Heap* heap, size_t valPos);
static int HeapGetMaxSonPos     (Heap* heap, size_t valPos);
static int HeapGetMinMaxGrandsonPos(Heap* heap, size_t valPos, CompareFunc Compare);
static int HeapGetMinGrandsonPos(Heap* heap, size_t valPos);
static int HeapGetMaxGrandsonPos(Heap* heap, size_t valPos);

static inline bool HeapValueLiesOnMinLevel(size_t valPos);

static void Swap(int* val1, int* val2);

static inline bool CompareMax       (int val1, int val2) { return val1 >= val2; }
static inline bool CompareMin       (int val1, int val2) { return val1 <= val2; }
static inline bool CompareMaxStrict (int val1, int val2) { return val1 >  val2; }
static inline bool CompareMinStrict (int val1, int val2) { return val1 <  val2; }

void ProcessMinMaxHeapQueries();

int main()
{
    ProcessMinMaxHeapQueries();
}

void ProcessMinMaxHeapQueries()
{
    Heap heap = HeapCtor();

    int m = 0;
    int scanfResult = scanf("%d", &m);
    assert(scanfResult == 1);

    int error = 0;

#define MAX_COMMAND_LEN 20
#define MAX_COMMAND_LEN_FORMAT_STR "19"

    char command[MAX_COMMAND_LEN] = "";

    while (m--)
    {
        scanfResult = scanf("%" MAX_COMMAND_LEN_FORMAT_STR "s", command);
        assert(scanfResult == 1);

        int valToPrint = 0;

        if (strcmp(command, "insert") == 0)
        {
            int n = 0;

            scanfResult = scanf("%d", &n);
            assert(scanfResult == 1);

            HeapInsert(&heap, n, &error);
            printf("ok\n");
        }
        else if (strcmp(command, "extract_min") == 0)
        {
            valToPrint = HeapExtractMin(&heap, &error);

            if (!error) printf("%d\n", valToPrint);
            else        printf("error\n");
        }
        else if (strcmp(command, "get_min") == 0)
        {
            valToPrint = HeapGetMin(&heap, &error);

            if (!error) printf("%d\n", valToPrint);
            else        printf("error\n");
        }
        else if (strcmp(command, "extract_max") == 0)
        {
            valToPrint = HeapExtractMax(&heap, &error);

            if (!error) printf("%d\n", valToPrint);
            else        printf("error\n");
        }
        else if (strcmp(command, "get_max") == 0)
        {
            valToPrint = HeapGetMax(&heap, &error);

            if (!error) printf("%d\n", valToPrint);
            else        printf("error\n");
        }
        else if (strcmp(command, "size") == 0)
            printf("%zu\n", HeapGetSize(&heap));
        else
        {
            HeapClear(&heap);

            printf("ok\n");
        }
    }

#undef MAX_COMMAND_LEN
#undef MAX_COMMAND_LEN_FORMAT_STR

    HeapDtor(&heap);
}

Array  ArrayCtor()
{
    Array arr = {};

    arr.data     = (int*)calloc(1, sizeof(int));
    arr.capacity = 1;
    arr.size     = 0;

    return arr;
}

Array  ArrayInit(size_t size)
{
    Array arr = {};

    arr.capacity = size;
    arr.size     = 0;

    arr.data = (int*)calloc(size, sizeof(*arr.data));

    return arr;
}

Array* ArrayDtor(Array* arr)
{
    assert(arr);

    arr->size     = 0;
    arr->capacity = 0;

    free(arr->data);
    arr->data = NULL;

    return NULL;
}

Array* ArrayClear(Array* arr)
{
    assert(arr);

    ArrayDtor(arr);
    *arr = ArrayCtor();

    return arr;
}

int ArrayPushBack(Array* arr, int val)
{
    assert(arr);
    assert(arr->size <= arr->capacity);

    if (arr->size == arr->capacity)
        if (ArraySizeIncrease(arr) == NULL)
            return -1;

    ArraySetVal(arr, arr->size, val);

    arr->size++;

    return 0;
}

int ArrayPopBack (Array* arr)
{
    assert(arr);

    if (arr->size * 4 <= arr->capacity)
        arr = ArraySizeDecrease(arr);

    if (arr->size == 0)
        return -1;

    arr->size--;

    return 0;
}

int ArrayGetVal(Array* arr, size_t index)
{
    assert(arr);
    assert(index < arr->capacity);

    return arr->data[index];
}

Array* ArraySetVal(Array* arr, size_t index, int val)
{
    assert(arr);
    assert(index < arr->capacity);

    arr->data[index] = val;

    return arr;
}

bool   ArrayIsEmpty(Array* arr)
{
    assert(arr);

    return arr->size == 0;
}

static Array* ArraySizeIncrease(Array* arr)
{
    assert(arr);
    assert(arr->size == arr->capacity);

    if (arr->capacity == 0)
        arr->capacity = 1;

    arr->capacity *= 2;

    void* tmp = realloc(arr->data, arr->capacity * sizeof(*arr->data));

    if (tmp == NULL)
        return NULL;

    arr->data = (int*)tmp;

    return arr;
}

static Array* ArraySizeDecrease(Array* arr)
{
    assert(arr);
    assert(arr->size * 4 <= arr->capacity);

    arr->capacity /= 2;

    arr->data = (int*)realloc(arr->data, arr->capacity * sizeof(*arr->data));

    return arr;
}

Heap  HeapCtor      ()
{
    Heap heap = {};
    heap.heapData = ArrayCtor();

    return heap;
}

Heap* HeapDtor      (Heap* heap)
{
    assert(heap);

    ArrayDtor(&heap->heapData);;

    return heap;
}

void   HeapInsert    (Heap* heap, int n, int* error)
{
    assert(heap);
    assert(error);

    *error = ArrayPushBack(&heap->heapData, n);
    if (*error) return;

    HeapSiftUp(heap, heap->heapData.size - 1, error);
}

int   HeapExtractMin(Heap* heap, int* error)
{
    assert(heap);
    assert(error);

    if (ArrayIsEmpty(&heap->heapData))
    {
        *error = 1;
        return 0;
    }

    int minVal = heap->heapData.data[0];

    heap->heapData.data[0] = heap->heapData.data[heap->heapData.size - 1];
    heap->heapData.size--;

    if (heap->heapData.size == 0)
        return minVal;

    HeapSiftDown(heap, 0ul, error);

    if (*error) return 0;

    return minVal;
}

int   HeapGetMin    (Heap* heap, int* error)
{
    assert(heap);
    assert(error);

    if (ArrayIsEmpty(&heap->heapData))
    {
        *error = 1;
        return 0;
    }

    return heap->heapData.data[0];
}

int   HeapExtractMax(Heap* heap, int* error)
{
    assert(heap);
    assert(error);

    if (heap->heapData.size == 0)
    {
        *error = 1;
        return 0;
    }

    if (heap->heapData.size == 1)
    {
        heap->heapData.size--;
        return heap->heapData.data[0];
    }

    int    maxVal    = heap->heapData.data[1];
    size_t maxValPos = 1ul;

    if (heap->heapData.size >= 3)
    {
        if (heap->heapData.data[2] > maxVal)
        {
            maxVal    = heap->heapData.data[2];
            maxValPos = 2ul;
        }
    }

    heap->heapData.size--;
    if (maxValPos == heap->heapData.size)
        return maxVal;

    heap->heapData.data[maxValPos] = heap->heapData.data[heap->heapData.size];

    HeapSiftDown(heap, maxValPos, error);

    if (*error) return 0;

    return maxVal;
}

int   HeapGetMax    (Heap* heap, int* error)
{
    assert(heap);
    assert(error);

    if (heap->heapData.size == 0)
    {
        *error = 1;
        return 0;
    }

    if (heap->heapData.size == 1)
        return heap->heapData.data[0];

    int    maxVal    = heap->heapData.data[1];
    size_t maxValPos = 1ul;

    if (heap->heapData.size >= 3)
    {
        if (heap->heapData.data[2] > maxVal)
        {
            maxVal    = heap->heapData.data[2];
            maxValPos = 2ul;
        }
    }

    return maxVal;
}

size_t   HeapGetSize   (Heap* heap)
{
    assert(heap);

    return heap->heapData.size;
}

void     HeapClear     (Heap* heap)
{
    assert(heap);

    ArrayClear(&heap->heapData);
}

static void HeapSiftUp  (Heap* heap, size_t valPos, int* error)
{
    assert(heap);
    assert(error);

    if (valPos == 0)
        return;

    int fatherPos = HeapGetFatherPos(valPos);
    if (HeapValueLiesOnMinLevel(valPos))
    {
        if (heap->heapData.data[valPos] > heap->heapData.data[fatherPos])
        {
            Swap(heap->heapData.data + valPos, heap->heapData.data + fatherPos);
            HeapSiftUpMax(heap, fatherPos, error);
        }
        else
            HeapSiftUpMin(heap, valPos, error);
    }
    else
    {
        if (heap->heapData.data[valPos] < heap->heapData.data[fatherPos])
        {
            Swap(heap->heapData.data + valPos, heap->heapData.data + fatherPos);
            HeapSiftUpMin(heap, fatherPos, error);
        }
        else
            HeapSiftUpMax(heap, valPos, error);
    }
}

static void HeapSiftUpMinMax(Heap* heap, size_t valPos, int* error, CompareFunc CompareStrict)
{
    assert(heap);
    assert(error);

    size_t currValPos = valPos;
    int grandpaPos = HeapGetGrandpaPos(valPos);
    while (grandpaPos != -1 && CompareStrict(heap->heapData.data[currValPos], heap->heapData.data[grandpaPos]))
    {
        Swap(heap->heapData.data + grandpaPos, heap->heapData.data + currValPos);
        currValPos = grandpaPos;
        grandpaPos = HeapGetGrandpaPos(currValPos);
    }  
}

static void HeapSiftUpMax  (Heap* heap, size_t valPos, int* error)
{
    assert(heap);
    assert(error);

    HeapSiftUpMinMax(heap, valPos, error, CompareMaxStrict);
}

static void HeapSiftUpMin  (Heap* heap, size_t valPos, int* error)
{
    assert(heap);
    assert(error);
    
    HeapSiftUpMinMax(heap, valPos, error, CompareMinStrict);
}

static void HeapSiftDown(Heap* heap, size_t valPos, int* error)
{
    assert(heap);
    assert(error);

    if (HeapValueLiesOnMinLevel(valPos))
        HeapSiftDownMin(heap, valPos, error);
    else
        HeapSiftDownMax(heap, valPos, error);
}

static void HeapSiftDownMinMax(Heap* heap, size_t valPos, int* error, CompareFunc CompareStrict,
                                                                      CompareFunc Compare)
{
    assert(heap);
    assert(error);

    int sonPos      = HeapGetMinMaxSonPos     (heap, valPos, Compare);
    int grandsonPos = HeapGetMinMaxGrandsonPos(heap, valPos, Compare);

    if (sonPos == -1)
        return;

    if ((grandsonPos == -1 || 
        CompareStrict(heap->heapData.data[sonPos], heap->heapData.data[grandsonPos])) &&
        CompareStrict(heap->heapData.data[sonPos], heap->heapData.data[valPos]))
    {
        Swap(heap->heapData.data + sonPos, heap->heapData.data + valPos);
        return;
    }

    if (grandsonPos == -1)
        return;

    if (CompareStrict(heap->heapData.data[grandsonPos], heap->heapData.data[valPos]))
    {
        Swap(heap->heapData.data + grandsonPos, heap->heapData.data + valPos);

        int grandsonFatherPos = HeapGetFatherPos(grandsonPos);
        if (CompareStrict(heap->heapData.data[grandsonFatherPos], heap->heapData.data[grandsonPos]))
            Swap(heap->heapData.data + grandsonPos, heap->heapData.data + grandsonFatherPos);

        HeapSiftDown(heap, grandsonPos, error);
    }
}

static void HeapSiftDownMin(Heap* heap, size_t valPos, int* error)
{
    assert(heap);
    assert(error);

    return HeapSiftDownMinMax(heap, valPos, error, CompareMinStrict, CompareMin);
}

static void HeapSiftDownMax(Heap* heap, size_t valPos, int* error)
{
    assert(heap);
    assert(error);

    return HeapSiftDownMinMax(heap, valPos, error, CompareMaxStrict, CompareMax);
}

static int HeapGetFatherPos     (size_t valPos)
{
    if (valPos == 0)
        return -1;

    return ((int)valPos - 1) / 2;
}

static int HeapGetGrandpaPos    (size_t valPos)
{
    int fatherPos = HeapGetFatherPos(valPos);

    if (fatherPos == -1)
        return -1;

    if (fatherPos == 0)
        return -1;

    return HeapGetFatherPos(fatherPos);
}

static int HeapGetMinMaxSonPos  (Heap* heap, size_t valPos, CompareFunc Compare)
{
    assert(heap);

    if (heap->heapData.size <= 2 * valPos + 1)
        return -1;

    int bestSonPos = 2 * (int)valPos + 1;
    
    if (heap->heapData.size <= bestSonPos + 1)
        return bestSonPos;

    if (Compare(heap->heapData.data[bestSonPos], heap->heapData.data[bestSonPos + 1]))
        return bestSonPos;
    
    return bestSonPos + 1;
}

static int HeapGetMinSonPos     (Heap* heap, size_t valPos)
{
    assert(heap);

    return HeapGetMinMaxSonPos(heap, valPos, CompareMin);
}

static int HeapGetMaxSonPos     (Heap* heap, size_t valPos)
{
    assert(heap);

    return HeapGetMinMaxSonPos(heap, valPos, CompareMax);
}

static int HeapGetMinMaxGrandsonPos(Heap* heap, size_t valPos, CompareFunc Compare)
{
    assert(heap);

    size_t leftSon  = valPos * 2 + 1;
    size_t rightSon = valPos * 2 + 2;

    int leftGrandSon  = HeapGetMinMaxSonPos(heap, leftSon, Compare);
    int rightGrandSon = HeapGetMinMaxSonPos(heap, rightSon, Compare);
    
    if (rightGrandSon == -1) return leftGrandSon;

    if (Compare(heap->heapData.data[leftGrandSon], heap->heapData.data[rightGrandSon]))
        return leftGrandSon;

    return rightGrandSon;
}

static int HeapGetMinGrandsonPos(Heap* heap, size_t valPos)
{
    assert(heap);

    return HeapGetMinMaxGrandsonPos(heap, valPos, CompareMin);
}

static int HeapGetMaxGrandsonPos(Heap* heap, size_t valPos)
{
    assert(heap);

    return HeapGetMinMaxGrandsonPos(heap, valPos, CompareMax);
}

static inline bool HeapValueLiesOnMinLevel(size_t valPos)
{
    return (int)log2((double)(valPos + 1)) % 2 == 0;
}

static void Swap(int* val1, int* val2)
{
    assert(val1);
    assert(val2);

    int temp = *val1;
    *val1 = *val2;
    *val2 = temp;
}
