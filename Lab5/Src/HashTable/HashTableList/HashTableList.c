#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "HashTableList.h"

static ListElem* ListElemCtor();
static ListElem* ListElemDtor(ListElem* elem);
static ListElem* ListElemInit(int key, ListElem* next);

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

ListElem* ListInsert  (List* list, ListElem* anchorElement, int key)
{
    assert(list);
    assert(anchorElement);
    assert(key);

    ListElem* elem = ListElemInit(key, anchorElement->nextElem);
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

void ListErase(List* list, int key)
{
    assert(list);
    assert(list->begin);

    ListElem* elem     = list->begin->nextElem;
    ListElem* prevElem = list->begin;

    while (elem != list->begin)
    {
        assert(elem);
        assert(prevElem);
        if (elem->key == key)
        {
            prevElem->nextElem = elem->nextElem;
            ListElemDtor(elem);
            break;
        }

        elem = elem->nextElem;
    }
}

ListElem* ListFindkey(List* list, int key)
{
    assert(list);
    assert(list->begin);

    ListElem* elem     = list->begin->nextElem;

    while (elem != list->begin)
    {
        assert(elem);
        if (elem->key == key)
        {
            return elem;
        }

        elem = elem->nextElem;
    }

    return NULL;
}

int ListGetkey(ListElem* elem)
{
    assert(elem);

    return elem->key;
}

ListElem* ListGetHead(List* list)
{
    assert(list);

    return list->begin->nextElem;
}

ListElem* ListFindVal(List* list, int key)
{
    assert(list);
    assert(list->begin);

    ListElem* elem = list->begin->nextElem;

    while (elem != list->begin)
    {
        if (elem->key == key)
            return elem;

        elem = elem->nextElem;
    }

    return NULL;
}

int ListGetVal(ListElem* elem)
{
    assert(elem);

    return elem->key;
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

    elem->key = 0;

    free(elem);
    return NULL;
}

static ListElem* ListElemInit(int key, ListElem* next)
{
    assert(key);

    ListElem* elem = ListElemCtor();

    if (elem == NULL)
        return NULL;

    elem->key = key;
    elem->nextElem = next;

    return elem;
}