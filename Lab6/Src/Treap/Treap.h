#ifndef TREAP_H
#define TREAP_H

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

void Insert(Treap* treap, int key);
void Delete(Treap* treap, int key);

#endif