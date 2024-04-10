#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct HeapDataType
{
    long long value;
    size_t commandId;
} HeapDataType;

HeapDataType HeapDataTypeCtor(long long value, size_t commandId);

typedef struct Array
{
    HeapDataType* data;

    size_t size;
    size_t capacity;
} Array;

Array ArrayCtor();

Array* ArrayDtor(Array* arr);

Array* ArrayClear(Array* arr);

long long ArrayPushBack(Array* arr, HeapDataType val);

long long ArrayPopBack(Array* arr);

long long ArrayGetVal(Array* arr, size_t index);

Array* ArraySetVal(Array* arr, size_t index, HeapDataType val);

static bool ArrayIsEmpty(Array* arr);

static Array* ArraySizeIncrease(Array* arr);

static Array* ArraySizeDecrease(Array* arr);

typedef struct Heap
{
    Array heapData;

    long long* commandsArray;
    size_t commandsArraySize;
    size_t commandsArrayCapacity;
} Heap;

Heap HeapCtor(size_t commandsArrSize);

Heap* HeapDtor(Heap* heap);

void HeapInsert(Heap* heap, long long val);

long long HeapGetMin(Heap* heap);

long long HeapExtractMin(Heap* heap);

void HeapDecreaseKey(Heap* heap, size_t commandId, long long delta);

static void HeapSiftUp(Heap* heap, size_t valPos);

static void HeapSiftDown(Heap* heap, size_t valPos);

static inline long long HeapGetFatherPos(long long valPos);

static inline long long HeapGetMinSonPos(Heap* heap, long long valPos);

static void Swap(HeapDataType* val1, HeapDataType* val2);

void ProcessQueries();

int main()
{
    ProcessQueries();
}

void ProcessQueries()
{
    size_t q = 0;
    int scanfRes = scanf("%zu", &q);
    assert(scanfRes == 1);

    Heap heap = HeapCtor(q);

    char command[20] = "";
    while (q--)
    {
        scanfRes = scanf("%s", command);
        assert(scanfRes == 1);

        if (strcmp(command, "insert") == 0)
        {
            long long x = 0;

            scanfRes = scanf("%lld", &x);
            assert(scanfRes == 1);

            HeapInsert(&heap, x);
        } else if (strcmp(command, "getMin") == 0)
            printf("%lld\n", HeapGetMin(&heap));
        else if (strcmp(command, "extractMin") == 0)
            HeapExtractMin(&heap);
        else
        {
            size_t i = 0;
            long long delta = 0;
            
            scanfRes = scanf("%zu%lld", &i, &delta);
            assert(scanfRes == 2);

            HeapDecreaseKey(&heap, i - 1, delta);
        }
    }
}

Array ArrayCtor()
{
    Array arr = {};

    arr.data = (HeapDataType*) calloc(1, sizeof(*arr.data));
    assert(arr.data);

    arr.capacity = 1;
    arr.size = 0;

    return arr;
}

Array ArrayInit(size_t size)
{
    Array arr = {};

    arr.capacity = size;
    arr.size = 0;

    arr.data = (HeapDataType*) calloc(size, sizeof(*arr.data));
    assert(arr.data);

    return arr;
}

Array* ArrayDtor(Array* arr)
{
    assert(arr);

    arr->size = 0;
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

long long ArrayPushBack(Array* arr, HeapDataType val)
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

long long ArrayPopBack(Array* arr)
{
    assert(arr);

    if (arr->size * 4 <= arr->capacity)
        arr = ArraySizeDecrease(arr);

    if (arr->size == 0)
        return -1;

    arr->size--;

    return 0;
}

long long ArrayGetVal(Array* arr, size_t index)
{
    assert(arr);

    assert(index < arr->capacity);

    return arr->data[index].value;
}

Array* ArraySetVal(Array* arr, size_t index, HeapDataType val)
{
    assert(arr);

    assert(index < arr->capacity);

    arr->data[index] = val;

    return arr;
}

bool ArrayIsEmpty(Array* arr)
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

    arr->data = (HeapDataType*) tmp;

    return arr;
}

static Array* ArraySizeDecrease(Array* arr)
{
    assert(arr);
    assert(arr->size * 4 <= arr->capacity);

    arr->capacity /= 2;

    arr->data = (HeapDataType*) realloc(arr->data, arr->capacity * sizeof(*arr->data));
    assert(arr->data);

    return arr;
}

HeapDataType HeapDataTypeCtor(long long value, size_t commandId)
{
    HeapDataType data =
            {
                    .value     = value,
                    .commandId = commandId
            };

    return data;
}

Heap HeapCtor(size_t commandsArrSize)
{
    Heap heap =
            {
                    .heapData              = ArrayCtor(),
                    .commandsArray         = (long long*) calloc(commandsArrSize,
                                                                 sizeof(long long)),
                    .commandsArrayCapacity = commandsArrSize,
                    .commandsArraySize     = 0
            };

    assert(heap.commandsArray);

    return heap;
}

Heap* HeapDtor(Heap* heap)
{
    assert(heap);

    ArrayDtor(&heap->heapData);

    return NULL;
}

void HeapInsert(Heap* heap, long long val)
{
    assert(heap);
    assert(heap->commandsArraySize <
           heap->commandsArrayCapacity);
    heap->commandsArray[heap->commandsArraySize++] = heap->heapData.size;

    ArrayPushBack(&heap->heapData, HeapDataTypeCtor(val, heap->commandsArraySize - 1));

    HeapSiftUp(heap, heap->heapData.size - 1);
}

long long HeapGetMin(Heap* heap)
{
    assert(heap);
    assert(heap->commandsArraySize < heap->commandsArrayCapacity);
    heap->commandsArray[heap->commandsArraySize++] = -1;

    return ArrayGetVal(&heap->heapData, 0);
}

long long HeapExtractMin(Heap* heap)
{
    assert(heap);
    assert(heap->commandsArraySize < heap->commandsArrayCapacity);
    heap->commandsArray[heap->commandsArraySize++] = -1;

    long long minVal = ArrayGetVal(&heap->heapData, 0);
    heap->heapData.size--;

    heap->heapData.data[0] = heap->heapData.data[heap->heapData.size];
    heap->commandsArray[heap->heapData.data[0].commandId] = 0;

    HeapSiftDown(heap, 0);

    return minVal;
}

void HeapDecreaseKey(Heap* heap, size_t commandId, long long delta)
{
    assert(heap);
    assert(heap->commandsArraySize < heap->commandsArrayCapacity);
    heap->commandsArray[heap->commandsArraySize++] = -1;

    static const long long INF = (long long) 1e17;
    long long* commandsArray = heap->commandsArray;

    long long savedVal = heap->heapData.data[commandsArray[commandId]].value;
    heap->heapData.data[commandsArray[commandId]].value = -INF;
    HeapSiftUp(heap, commandsArray[commandId]);

    heap->heapData.data[0].value = savedVal - delta;
    HeapSiftDown(heap, 0);
}

static void HeapSiftUp(Heap* heap, size_t valPos)
{
    assert(heap);

    long long curPos = (long long) valPos;

    long long* commandsArray = heap->commandsArray;

    long long fatherPos = HeapGetFatherPos(curPos);
    while (fatherPos != -1 &&
           heap->heapData.data[curPos].value < heap->heapData.data[fatherPos].value)
    {
        Swap(&heap->heapData.data[curPos], &heap->heapData.data[fatherPos]);
        commandsArray[heap->heapData.data[curPos].commandId] = curPos;
        commandsArray[heap->heapData.data[fatherPos].commandId] = fatherPos;

        curPos = fatherPos;
        fatherPos = HeapGetFatherPos(curPos);
    }
}

static void HeapSiftDown(Heap* heap, size_t valPos)
{
    assert(heap);

    long long curPos = (long long) valPos;

    long long* commandsArray = heap->commandsArray;

    long long minChildPos = HeapGetMinSonPos(heap, curPos);
    while (minChildPos != -1 &&
           heap->heapData.data[curPos].value > heap->heapData.data[minChildPos].value)
    {
        Swap(&heap->heapData.data[curPos], &heap->heapData.data[minChildPos]);
        commandsArray[heap->heapData.data[curPos].commandId] = curPos;
        commandsArray[heap->heapData.data[minChildPos].commandId] = minChildPos;

        curPos = minChildPos;
        minChildPos = HeapGetMinSonPos(heap, curPos);
    }

}

static inline long long HeapGetFatherPos(long long valPos)
{
    if (valPos == 0)
        return -1;

    return (valPos - 1) / 2;
}

static inline long long HeapGetMinSonPos(Heap* heap, long long valPos)
{
    assert(heap);

    if (valPos * 2 + 1 >= heap->heapData.size)
        return -1;

    long long minPos = valPos * 2 + 1;

    if (minPos + 1 >= heap->heapData.size ||
        heap->heapData.data[minPos].value <= heap->heapData.data[minPos + 1].value)
        return minPos;

    return minPos + 1;
}

static void Swap(HeapDataType* val1, HeapDataType* val2)
{
    assert(val1);
    assert(val2);

    HeapDataType tmp = *val1;
    *val1 = *val2;
    *val2 = tmp;
}
