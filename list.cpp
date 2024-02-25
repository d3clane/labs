#include <string.h>
#include <stdlib.h>

#include "List.h"

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
    ListElem* elem = ListElemInit(val, valSize, anchorElement->nextElem);
    anchorElement->nextElem = elem;

    return elem;
}

ListElem* ListPopHead(List* list)
{
    ListElem* elem    = ListGetHead(list);
    ListElem* newHead = elem->nextElem;

    ListElemDtor(elem);
    list->begin->nextElem = newHead;

    return newHead;
}

void* ListGetVal(ListElem* elem)
{
    return elem->value;
}

ListElem* ListGetHead(List* list)
{
    return list->begin->nextElem;
}

static ListElem* ListElemCtor()
{
    ListElem* elem = (ListElem*)calloc(1, sizeof(*elem));

    return elem;
}

static ListElem* ListElemDtor(ListElem* elem)
{
    elem->nextElem = NULL;

    free(elem->value);
    elem->value     = NULL;
    elem->valueSize = 0;

    free(elem);
    return NULL;
}

static ListElem* ListElemInit(void* val, size_t valSize, ListElem* next)
{
    ListElem* elem = ListElemCtor();

    elem->value    = calloc(1, valSize);
    memcpy(val, elem->value, valSize);

    elem->nextElem = next;

    return elem;
}
