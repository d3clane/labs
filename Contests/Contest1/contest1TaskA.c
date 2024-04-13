#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Array
{
    int* data;

    size_t size;
    size_t capacity;
} Array;

static Array* ArraySizeIncrease(Array* arr);
static Array* ArraySizeDecrease(Array* arr);

Array  ArrayCtor();
Array  ArrayInit(size_t size);
Array* ArrayDtor(Array* arr);
int ArrayPushBack(Array* arr, int val);
int ArrayPopBack (Array* arr, int* error);
int ArrayGetVal(Array* arr, size_t index);
Array* ArraySetVal(Array* arr, size_t index, int val);
bool ArrayIsEmpty(Array* arr);
size_t ArrayGetSize(Array* arr);
void ArrayClear(Array* arr);

typedef struct Stack
{
    Array data;
} Stack;

Stack StackCtor();
void  StackDtor(Stack* stk);
void StackPush(Stack* stack, int n);
int StackIsEmpty(Stack* stack);
int StackPop(Stack* stack, int* error);
int StackGetBack(Stack* stack, int* error);
size_t StackGetSize(Stack* stack);
void StackClear(Stack* stack);

void ProcessQueries();

int main()
{
    ProcessQueries();
}

void ProcessQueries()
{
    Stack stack = StackCtor();
    char commandName[6] = "";

    while (true)
    {
        scanf("%s", commandName);
        int error = 0;
        if (strcmp(commandName, "push") == 0)
        {
            int value = 0;
            int scanfRes = scanf("%d", &value);
            assert(scanfRes == 1);
            
            StackPush(&stack, value);
            printf("ok\n");
        }
        else if (strcmp(commandName, "pop") == 0)
        {
            int val = StackPop(&stack, &error);
            if (error)
                printf("error\n");
            else
                printf("%d\n", val);
        }
        else if (strcmp(commandName, "back") == 0)
        {
            int val = StackGetBack(&stack, &error);
            if (error)
                printf("error\n");
            else
                printf("%d\n", val);
        }
        else if (strcmp(commandName, "size") == 0)
        {
            printf("%zu\n", StackGetSize(&stack));
        }
        else if (strcmp(commandName, "clear") == 0)
        {
            StackClear(&stack);
            printf("ok\n");
        }
        else if (strcmp(commandName, "exit") == 0)
        {
            printf("bye\n");
            break;
        }
    }

    StackDtor(&stack);
}

Array  ArrayCtor()
{
    Array arr = {};

    arr.data     = NULL;
    arr.capacity = 0;
    arr.size     = 0;

    return arr;
}

Array  ArrayInit(size_t size)
{
    Array arr = {};

    arr.capacity = size;
    arr.size     = 0;

    arr.data = calloc(size, sizeof(*arr.data));
    assert(arr.data);

    return arr;
}

Array* ArrayDtor(Array* arr)
{
    arr->size     = 0;
    arr->capacity = 0;

    free(arr->data);
    arr->data = NULL;

    return NULL;
}

int ArrayPushBack(Array* arr, int val)
{
    assert(arr->size <= arr->capacity);

    if (arr->size == arr->capacity)
        if (ArraySizeIncrease(arr) == NULL)
            return 0;

    ArraySetVal(arr, arr->size, val);

    arr->size++;

    return 1;
}

int ArrayPopBack (Array* arr, int* error)
{
    assert(error);

    if (arr->size * 4 <= arr->capacity)
        arr = ArraySizeDecrease(arr);

    if (arr->size == 0)
    {
        *error = 1;
        return 0;
    }

    arr->size--;

    return 1;
}

int ArrayGetVal(Array* arr, size_t index)
{
    assert(index < arr->capacity);

    return arr->data[index];
}

Array* ArraySetVal(Array* arr, size_t index, int val)
{
    assert(index < arr->capacity);

    arr->data[index] = val;

    return arr;
}

bool ArrayIsEmpty(Array* arr)
{
    return arr->size == 0;
}

size_t ArrayGetSize(Array* arr)
{
    return arr->size;
}

void ArrayClear(Array* arr)
{
    ArrayDtor(arr);
    *arr = ArrayCtor();
}

static Array* ArraySizeIncrease(Array* arr)
{
    assert(arr->size == arr->capacity);

    if (arr->capacity == 0)
        arr->capacity++;

    arr->capacity *= 2;

    void* tmp = realloc(arr->data, arr->capacity * sizeof(*arr->data));

    if (tmp != NULL)
        arr->data = (int*)tmp;

    return arr;
}

static Array* ArraySizeDecrease(Array* arr)
{
    assert(arr->size * 4 <= arr->capacity);

    arr->capacity /= 2;

    void* tmp = realloc(arr->data, arr->capacity * sizeof(*arr->data));

    if (tmp != NULL)
        arr->data = (int*)tmp;

    return arr;
}


Stack StackCtor()
{
    Stack stk = {};

    stk.data = ArrayCtor();
    return stk;
}

void StackDtor(Stack* stk)
{
    ArrayDtor(&stk->data);
}

void StackPush(Stack* stack, int n)
{
    ArrayPushBack(&stack->data, n);
}

int StackIsEmpty(Stack* stack)
{
    return ArrayIsEmpty(&stack->data);
}

int StackPop(Stack* stack, int* error)
{
    assert(error);

    if (StackIsEmpty(stack))
    {
        *error = 1;
        return 0;
    }

    int val = ArrayGetVal(&stack->data, ArrayGetSize(&stack->data) - 1);
    ArrayPopBack(&stack->data, error);

    return val;
}

int StackGetBack(Stack* stack, int* error)
{
    assert(error);

    if (StackIsEmpty(stack))
    {
        *error = 1;
        return 0;
    }

    return ArrayGetVal(&stack->data, ArrayGetSize(&stack->data) - 1);
}

size_t StackGetSize(Stack* stack)
{
    return ArrayGetSize(&stack->data);
}

void StackClear(Stack* stack)
{
    ArrayClear(&stack->data);
}
