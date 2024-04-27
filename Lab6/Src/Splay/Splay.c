#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "Splay.h"

static SplayNodesPair Split (SplayNode* tree, const int key);
static SplayNode* Merge     (SplayNode* tree1, SplayNode* tree2);

static void Splay                       (SplayNode* node);

static inline void RotateLeft           (SplayNode* node);
static inline void RotateRight          (SplayNode* node);

static inline SplayNode* GetMaxNode     (SplayNode* root);

static inline SplayNode* GetParent      (SplayNode* node);
static inline SplayNode* GetGrandParent (SplayNode* node);

SplayTree SplayTreeCtor()
{
    SplayTree tree =
            {
                    .root = NULL,
            };

    return tree;
}

SplayNode* SplayNodeCtor(const int key)
{
    SplayNode* node = (SplayNode*) calloc(1, sizeof(*node));
    assert(node);

    node->key = key;

    node->left = node->right = node->parent = NULL;

    return node;
}

void SplayOneNodeDtor(SplayNode* node)
{
    node->key = 0;

    node->left = node->right = node->parent = NULL;

    free(node);
}

void SplaySubtreeDtor(SplayNode* node)
{
    if (node == NULL)
        return;

    SplaySubtreeDtor(node->left);
    SplaySubtreeDtor(node->right);
    SplayOneNodeDtor(node);
}

void SplayTreeDtor(SplayTree* tree)
{
    if (!tree)
        return;
    
    SplaySubtreeDtor(tree->root);
}

SplayNode* GetParent(SplayNode* node)
{
    return node ? node->parent : NULL;
}

SplayNode* GetGrandParent(SplayNode* node)
{
    return GetParent(GetParent(node));
}

static inline void RotateLeft(SplayNode* node)
{
    assert(node);
    assert(node->right);

    SplayNode* parent = GetParent(node);

    SplayNode* tmp = node->right;
    node->right = tmp->left;
    tmp->left = node;

    node->parent = tmp;
    tmp->parent = parent;

    if (node->right)
        node->right->parent = node;

    if (!parent)
        return;

    if (parent->left == node)
        parent->left = tmp;
    else
        parent->right = tmp;
}

static inline void RotateRight(SplayNode* node)
{
    assert(node);
    assert(node->left);

    SplayNode* parent = GetParent(node);

    SplayNode* tmp = node->left;
    node->left = tmp->right;
    tmp->right = node;

    node->parent = tmp;
    tmp->parent = parent;

    if (node->left)
        node->left->parent = node;

    if (!parent)
        return;

    if (parent->left == node)
        parent->left = tmp;
    else
        parent->right = tmp;
}

static void Splay(SplayNode* node)
{
    SplayNode* parent = GetParent(node);
    SplayNode* grandParent = GetGrandParent(node);

    while (parent)
    {
        if (node == parent->left)
        {
            if (grandParent == NULL)                // zig
                RotateRight(parent);
            else if (grandParent->left == parent)   // zig zig
            {
                RotateRight(grandParent);
                RotateRight(parent);
            } else                                  // zig zag
            {
                RotateRight(parent);
                RotateLeft(grandParent);
            }
        } else
        {
            if (grandParent == NULL)
                RotateLeft(parent);
            else if (grandParent->right == parent)
            {
                RotateLeft(grandParent);
                RotateLeft(parent);
            } else
            {
                RotateLeft(parent);
                RotateRight(grandParent);
            }
        }

        parent = GetParent(node);
        grandParent = GetGrandParent(node);
    }
}

SplayNodesPair SplayNodesPairCtor(SplayNode* node1, SplayNode* node2)
{
    SplayNodesPair pair =
            {
                    .node1 = node1,
                    .node2 = node2,
            };

    return pair;
}

static SplayNodesPair Split(SplayNode* tree, const int key)
{
    SplayNode* node = tree;
    SplayNode* nearestNode = NULL;

    while (node)
    {  
        if (key == node->key)
        {
            nearestNode = node;
            break;
        }

        if (key < node->key)
            node = node->left;
        else
        {
            nearestNode = node;
            node = node->right;
        }
    }

    Splay(nearestNode);

    SplayNodesPair pair = {};

    if (nearestNode == NULL)
        pair = SplayNodesPairCtor(NULL, tree);
    else
    {
        pair = SplayNodesPairCtor(nearestNode, nearestNode->right);
        if (nearestNode->right) nearestNode->right->parent = NULL;
        nearestNode->right = NULL;
    }

    return pair;
}

static SplayNode* Merge(SplayNode* tree1, SplayNode* tree2)
{
    if (tree1 == NULL)
        return tree2;
    
    // fprintf(stderr, "MAX NODE GET BEGIN\n");
    SplayNode* maxNode = GetMaxNode(tree1);
    // fprintf(stderr, "MAX NODE GET END\n");
    Splay(maxNode);

    // fprintf(stderr, "SPLAY END\n");

    assert(maxNode);
    assert(maxNode->right != maxNode);
    if (maxNode->right != NULL)
    {
        // fprintf(stderr, "MY VAL - %d, right val - %d\n", maxNode->key, maxNode->right->key);
    }
    
    assert(maxNode->right == NULL);

    maxNode->right  = tree2;

    assert(maxNode->parent == NULL); 

    if (tree2) 
        tree2->parent = maxNode;

    return maxNode;
}

static inline SplayNode* GetMaxNode(SplayNode* root)
{
    if (root == NULL)
        return NULL;

    SplayNode* node = root;

    while (node->right)
        node = node->right;

    
    return node;
}

void SplayInsert(SplayTree* tree, const int key)
{
    SplayNodesPair pair = Split(tree->root, key);
    
    if (pair.node1 && pair.node1->key == key)
    {
        // fprintf(stderr, "MERGE START\n");
        tree->root = Merge(pair.node1, pair.node2);
        // fprintf(stderr, "MERGE END\n");
        return;
    }

    SplayNode* newNode = SplayNodeCtor(key);

    newNode->left = pair.node1;
    if (pair.node1) pair.node1->parent = newNode;

    newNode->right = pair.node2;
    if (pair.node2) pair.node2->parent = newNode;

    tree->root = newNode;
}

void SplayDelete(SplayTree* tree, const int key)
{
    assert(tree);

    SplayNode* prevNode = NULL;
    SplayNode* node     = tree->root;

    // fprintf(stderr, "WHILE START\n");
    while (node && node->key != key)
    {
        prevNode = node;

        assert(node != node->left);
        assert(node != node->right);
        if (key < node->key)
            node = node->left;
        else
            node = node->right;

        //// fprintf(stderr, "WHILE STEP\n");
    }

    // fprintf(stderr, "WHILE END\n");

    if (node == NULL)
    {
        Splay(prevNode);

        return;
    }

    // fprintf(stderr, "START SPLAY\n");
    
    Splay(node);

    // fprintf(stderr, "SPLAY END\n");

    assert(node);

    // fprintf(stderr, "START MERGE\n");

    if (node->left)  node->left->parent = NULL;
    if (node->right) node->right->parent = NULL;
    tree->root = Merge(node->left, node->right);
    // fprintf(stderr, "MERGE END\n");

    // fprintf(stderr, "DTOR START\n");
    SplayOneNodeDtor(node);
    // fprintf(stderr, "DTOR END\n");
}
