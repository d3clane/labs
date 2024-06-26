#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "list.h"

static ListElem* ListElemCtor();
static ListElem* ListElemDtor(ListElem* elem);
static ListElem* ListElemInit(void* val, size_t valSize, ListElem* next);

List ListCtor(size_t elemSize)
{
    List list = 
    {
        .begin = ListElemCtor(),

        .elemSize = elemSize,
    };

    list.begin->nextElem = list.begin;
    list.size = 0;
    
    return list;
}

List* ListDtor(List* list)
{
    ListElem* elem = list->begin;
    ListElem* next = NULL;
    while (next != list->begin)
    {
        next = elem->nextElem;
        ListElemDtor(elem);
        elem = next;
    }

    return NULL;
}

ListElem* ListInsert  (List* list, ListElem* anchorElement, void* val)
{
    assert(list);
    assert(anchorElement);
    assert(val);

    ListElem* elem = ListElemInit(val, list->elemSize, anchorElement->nextElem);
    anchorElement->nextElem = elem;

    list->size++;

    return elem;
}

int ListPopHead(List* list)
{
    assert(list);

    ListElem* elem = ListGetHead(list);

    if (elem == NULL)
        return 0;

    ListElem* newHead = elem->nextElem;

    ListElemDtor(elem);
    list->begin->nextElem = newHead;

    list->size--;

    return 0;
}

void* ListGetVal(ListElem* elem)
{
    assert(elem);

    return elem->value;
}

ListElem* ListGetHead(List* list)
{
    assert(list);

    return list->begin->nextElem;
}

static ListElem* ListElemCtor()
{
    ListElem* elem = (ListElem*)calloc(1, sizeof(*elem));
    assert(elem);

    return elem;
}

static ListElem* ListElemDtor(ListElem* elem)
{
    assert(elem);

    elem->nextElem = NULL;

    free(elem->value);
    elem->value     = NULL;

    free(elem);
    return NULL;
}

static ListElem* ListElemInit(void* val, size_t valSize, ListElem* next)
{
    assert(val);

    ListElem* elem = ListElemCtor();

    if (elem == NULL)
        return NULL;

    elem->value     = calloc(1, valSize);
    assert(elem->value);
    
    memcpy(elem->value, val, valSize);

    elem->nextElem = next;

    return elem;
}
