#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "HashTableList.h"

static ListElem* ListElemCtor();
static ListElem* ListElemDtor(ListElem* elem);
static ListElem* ListElemInit(int val, ListElem* next);

List ListCtor()
{
    List list = 
    {
        .begin = ListElemCtor(),
        .size  = 0,
    };

    assert(list.begin);
    list.begin->nextElem = list.begin;
    
    return list;
}

List* ListDtor(List* list)
{
    if (list == NULL)
        return NULL;

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

ListElem* ListInsert  (List* list, ListElem* anchorElement, int val)
{
    assert(list);
    assert(anchorElement);
    assert(val);

    ListElem* elem = ListElemInit(val, anchorElement->nextElem);
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

void ListErase(List* list, int val)
{
    assert(list);
    assert(list->begin);

    ListElem* elem     = list->begin->nextElem;
    ListElem* prevElem = list->begin;

    while (elem != list->begin)
    {
        assert(elem);
        assert(prevElem);
        if (elem->value == val)
        {
            prevElem->nextElem = elem->nextElem;
            ListElemDtor(elem);
            break;
        }

        elem = elem->nextElem;
    }
}

ListElem* ListFindVal(List* list, int val)
{
    assert(list);
    assert(list->begin);

    ListElem* elem     = list->begin->nextElem;

    while (elem != list->begin)
    {
        assert(elem);
        if (elem->value == val)
        {
            return elem;
        }

        elem = elem->nextElem;
    }

    return NULL;
}

int ListGetVal(ListElem* elem)
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

static ListElem* ListElemInit(int val, ListElem* next)
{
    assert(val);

    ListElem* elem = ListElemCtor();

    if (elem == NULL)
        return NULL;

    elem->value = val;
    elem->nextElem = next;

    return elem;
}