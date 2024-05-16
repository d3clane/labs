#ifndef TREAP_H
#define TREAP_H

#include <stdbool.h>

typedef struct TreapNode
{
    int key;
    int priority;

    struct TreapNode* leftSon;
    struct TreapNode* rightSon;
} TreapNode;

typedef struct Treap
{
    TreapNode* root;
} Treap;

TreapNode* TreapNodeCtor(int key);
void       TreapNodeDtor(TreapNode* node);

Treap TreapCtor();
void  TreapDtor(Treap* tree);

void TreapInsert(Treap* treap, int key);
void TreapDelete(Treap* treap, int key);
bool TreapExist (Treap* treap, int key);

#endif