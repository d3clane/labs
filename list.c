#include <assert.h>
#include <string.h>
#include <stdlib.h>

#include "list.h"

static ListElem* ListElemCtor();
static ListElem* ListElemDtor(ListElem* elem);
static ListElem* ListElemInit(void* val, size_t valSize, ListElem* next);

List ListCtor()
{
    List list = 
    {
        .begin = ListElemCtor()
    };

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

ListElem* ListInsert  (List* list, ListElem* anchorElement, void* val, size_t valSize)
{
    assert(list);
    assert(anchorElement);
    assert(val);

    ListElem* elem = ListElemInit(val, valSize, anchorElement->nextElem);
    anchorElement->nextElem = elem;

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

    return elem;
}

static ListElem* ListElemDtor(ListElem* elem)
{
    assert(elem);

    elem->nextElem = NULL;

    free(elem->value);
    elem->value     = NULL;
    elem->valueSize = 0;

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
    elem->valueSize = valSize;
    memcpy(elem->value, val, valSize);

    elem->nextElem = next;

    return elem;
}
