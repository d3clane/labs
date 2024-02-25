#ifndef LIST_H
#define LIST_H

#include <stddef.h>

typedef struct ListElem
{
    void* value;
    size_t valueSize;

    struct ListElem* nextElem;
} ListElem;

typedef struct List
{
    ListElem* begin;
    
    size_t size;
} List;

List  ListCtor();
List* ListDtor(List* list);

ListElem* ListInsert(List* list, ListElem* anchorElement, void* val, size_t valSize);
int ListPopHead     (List* list);

void* ListGetVal(ListElem* elem);

ListElem* ListGetHead(List* list);

#endif
