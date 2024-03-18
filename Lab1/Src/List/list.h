#ifndef LIST_H
#define LIST_H

#include <stddef.h>

typedef struct ListElem
{
    void* value;

    struct ListElem* nextElem;
} ListElem;

typedef struct List
{
    ListElem* begin;
    
    size_t size;

    size_t elemSize;
} List;

List  ListCtor(size_t elemSize);
List* ListDtor(List* list);

ListElem* ListInsert(List* list, ListElem* anchorElement, void* val);
int ListPopHead     (List* list);

void* ListGetVal(ListElem* elem);

ListElem* ListGetHead(List* list);

#endif
