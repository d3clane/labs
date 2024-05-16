#include "Treap.h"

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct TreapNodesPair
{
    TreapNode* node1;
    TreapNode* node2;
} TreapNodesPair;

static inline TreapNodesPair TreapNodesPairCtor(TreapNode* node1, TreapNode* node2);
TreapNode* TreapNodeCtor(int key);
void       TreapNodeDtor(TreapNode* node);

Treap TreapCtor();
void  TreapDtor(Treap* tree);
static void TreapDtorRecursively(TreapNode* node);

static TreapNodesPair Split(TreapNode* tree, int key);
static TreapNode* Merge(TreapNode* tree1, TreapNode* tree2);

void TreapInsert(Treap* treap, int key);
void TreapDelete(Treap* treap, int key);

static inline TreapNodesPair TreapNodesPairCtor(TreapNode* node1, TreapNode* node2)
{
    TreapNodesPair TreapNodesPair =
            {
                    .node1 = node1,
                    .node2 = node2,
            };

    return TreapNodesPair;
}

TreapNode* TreapNodeCtor(int key)
{
    TreapNode* treapNode = (TreapNode*)calloc(1, sizeof(*treapNode));
    assert(treapNode);

    treapNode->key = key;
    treapNode->priority = rand();

    treapNode->leftSon     = NULL;
    treapNode->rightSon    = NULL;

    return treapNode;
}

void       TreapNodeDtor(TreapNode* node)
{
    if (node == NULL)
        return;
    
    node->key = 0;
    node->priority = 0;

    node->leftSon = NULL;
    node->rightSon = NULL;

    free(node);
}

Treap TreapCtor()
{
    Treap treap =
            {
                .root = NULL,
            };

    return treap;
}

static void TreapDtorRecursively(TreapNode* node)
{
    if (!node)
        return;

    TreapDtorRecursively(node->leftSon);
    TreapDtorRecursively(node->rightSon);

    TreapNodeDtor(node);
}

void  TreapDtor(Treap* tree)
{
    if (tree == NULL)
        return;

    TreapDtorRecursively(tree->root);
}

static TreapNodesPair Split(TreapNode* tree, int key)
{
    if (tree == NULL)
        return TreapNodesPairCtor(NULL, NULL);

    TreapNodesPair pair = {};

    if (key < tree->key)
    {
        pair = Split(tree->leftSon, key);
        tree->leftSon = pair.node2;
        return TreapNodesPairCtor(pair.node1, tree);
    } else
    {
        pair = Split(tree->rightSon, key);
        tree->rightSon = pair.node1;
        return TreapNodesPairCtor(tree, pair.node2);
    }
}

static TreapNode* Merge(TreapNode* tree1, TreapNode* tree2)
{
    if (tree1 == NULL) return tree2;
    if (tree2 == NULL) return tree1;

    if (tree1->priority < tree2->priority)
    {
        tree2->leftSon = Merge(tree1, tree2->leftSon);
        return tree2;
    } else
    {
        tree1->rightSon = Merge(tree1->rightSon, tree2);
        return tree1;
    }
}

void TreapInsert(Treap* treap, int key)
{
    assert(treap);

    if (TreapExist(treap, key))
        return;
        
    TreapNodesPair pair = Split(treap->root, key);

    treap->root = Merge(Merge(pair.node1, TreapNodeCtor(key)), pair.node2);
}

void TreapDelete(Treap* treap, int key)
{
    assert(treap);

    assert(treap);

    TreapNode* deleteNode = treap->root;
    TreapNode* prevNode   = NULL;
    while (deleteNode && deleteNode->key != key)
    {
        prevNode = deleteNode;

        if (key < deleteNode->key)
            deleteNode = deleteNode->leftSon;
        else
            deleteNode = deleteNode->rightSon;
    }

    if (deleteNode == NULL)
        return;

    if (prevNode == NULL)
    {
        treap->root = Merge(deleteNode->leftSon, deleteNode->rightSon);
    }
    else
    {
        if (prevNode->leftSon == deleteNode)
            prevNode->leftSon  = Merge(deleteNode->leftSon, deleteNode->rightSon);
        else
            prevNode->rightSon = Merge(deleteNode->leftSon, deleteNode->rightSon);
    }

    TreapNodeDtor(deleteNode);
}

bool TreapExist (Treap* treap, int key)
{
    assert(treap);

    if (treap->root == NULL)
        return false;

    TreapNode* node = treap->root;

    while (node && node->key != key)
    {
        if (key < node->key)
            node = node->leftSon;
        else 
            node = node->rightSon;
    }

    if (node == NULL)
        return false;

    return true;
}