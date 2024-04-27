#ifndef SPLAY_H
#define SPLAY_H

typedef struct SplayNode
{
    int key;

    struct SplayNode* left;
    struct SplayNode* right;

    struct SplayNode* parent;
} SplayNode;

typedef struct SplayTree
{
    SplayNode* root;
} SplayTree;

typedef struct SplayNodesPair
{
    SplayNode* node1;
    SplayNode* node2;
} SplayNodesPair;

SplayTree SplayTreeCtor();
SplayNode* SplayNodeCtor(const int key);
void SplayOneNodeDtor(SplayNode* node);
void SplayDtor(SplayNode* node);

SplayNodesPair SplayNodesPairCtor(SplayNode* node1, SplayNode* node2);

void Insert(SplayTree* tree, const int key);
void Delete(SplayTree* tree, const int key);

#endif
