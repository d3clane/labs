#ifndef LIST_H
#define LIST_H

#include <stddef.h>

typedef struct ListElem
{
    int key;

    struct ListElem* nextElem;
} ListElem;

typedef struct List
{
    ListElem* begin;
    
    size_t size;
} List;

List  ListCtor();
List* ListDtor(List* list);

ListElem* ListInsert(List* list, ListElem* anchorElement, int key);
void      ListErase(List* list, int key);
ListElem* ListFindKey(List* list, int key);

int ListPopHead     (List* list);

int ListGetKey(ListElem* elem);

ListElem* ListGetHead(List* list);

#endif