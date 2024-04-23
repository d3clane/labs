#ifndef LIST_H
#define LIST_H

#include <stddef.h>

typedef struct ListElem
{
    int value;

    struct ListElem* nextElem;
} ListElem;

typedef struct List
{
    ListElem* begin;
    
    size_t size;
} List;

List  ListCtor();
List* ListDtor(List* list);

ListElem* ListInsert(List* list, ListElem* anchorElement, int val);
void      ListErase(List* list, int val);
ListElem* ListFindVal(List* list, int val);

int ListPopHead     (List* list);

int ListGetVal(ListElem* elem);

ListElem* ListGetHead(List* list);

#endif