#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "AVL.h"

static inline size_t Max(size_t val1, size_t val2) { return val1 < val2 ? val2 : val1; }

static inline bool AVLNeedRotateLeft(AVLNode* node);
static inline bool AVLNeedRotateRight(AVLNode* node);
static inline void UpdateHeights(AVLNode* node);
static inline AVLNode* AVLRotateLeft(AVLNode* node);
static inline AVLNode* AVLRotateRight(AVLNode* node);
static inline int GetDiff(AVLNode* node);

static inline AVLNode* AVLBigRotateLeft(AVLNode* node);
static inline AVLNode* AVLBigRotateRight(AVLNode* node);
static inline AVLNode* AVLRotate(AVLNode* node);

static inline AVLNode* UntieMaxNode(AVLNode* root, AVLNode** maxNode);

AVLNode* AVLNodeCtor(int key)
{
    AVLNode* node = (AVLNode*) calloc(1, sizeof(*node));
    assert(node);

    node->key = key;

    node->subtreeHeight = 1;

    node->left = NULL;
    node->right = NULL;

    return node;
}

AVL AVLCtor()
{
    AVL tree =
            {
                    .root = NULL,
            };

    return tree;
}

void AVLDtorOneNode(AVLNode* node)
{
    node->key = 0;

    node->subtreeHeight = 0;

    node->right = NULL;
    node->left  = NULL;

    free(node);
}

void AVLDtorNodeRecursively(AVLNode* node)
{
    if (node == NULL)
        return;

    AVLDtorNodeRecursively(node->left);
    AVLDtorNodeRecursively(node->right);

    AVLDtorOneNode(node);
}

void AVLDtor(AVL* tree)
{
    if (tree == NULL)
        return;

    if (tree->root == NULL)
        return;
}

void AVLNodeSetkey(AVLNode* node, int key)
{
    assert(node);

    node->key = key;
}

void AVLNodeInit(AVLNode* node, int key)
{
    assert(node);

    node->key = key;

    node->left = NULL;
    node->right = NULL;

    node->subtreeHeight = 1;
}

static inline bool AVLNeedRotateLeft(AVLNode* node)
{
    if (node == NULL) return false;

    size_t leftSubtreeSize = node->left ? node->left->subtreeHeight : 0;
    size_t rightSubtreeSize = node->right ? node->right->subtreeHeight : 0;

    assert(rightSubtreeSize <= leftSubtreeSize + 2);

    return rightSubtreeSize >= leftSubtreeSize + 2;
}

static inline bool AVLNeedRotateRight(AVLNode* node)
{
    if (node == NULL) return false;

    size_t leftSubtreeSize = node->left ? node->left->subtreeHeight : 0;
    size_t rightSubtreeSize = node->right ? node->right->subtreeHeight : 0;

    assert(leftSubtreeSize <= rightSubtreeSize + 2);

    return leftSubtreeSize >= rightSubtreeSize + 2;
}

static inline void UpdateHeights(AVLNode* node)
{
    if (node == NULL)
        return;

    size_t leftSubtreeSize = node->left ? node->left->subtreeHeight : 0;
    size_t rightSubtreeSize = node->right ? node->right->subtreeHeight : 0;

    node->subtreeHeight = Max(leftSubtreeSize, rightSubtreeSize) + 1;
}

static inline AVLNode* AVLRotateLeft(AVLNode* node)
{
    AVLNode* tmp = node->right;
    node->right = tmp->left;
    tmp->left = node;

    UpdateHeights(node);
    UpdateHeights(tmp);

    return tmp;
}

static inline AVLNode* AVLRotateRight(AVLNode* node)
{
    AVLNode* tmp = node->left;
    node->left = tmp->right;
    tmp->right = node;

    UpdateHeights(node);
    UpdateHeights(tmp);

    return tmp;
}

static inline int GetDiff(AVLNode* node)
{
    size_t leftSubtreeSize = node->left ? node->left->subtreeHeight : 0;
    size_t rightSubtreeSize = node->right ? node->right->subtreeHeight : 0;

    return (int)(rightSubtreeSize - leftSubtreeSize);
}

static inline AVLNode* AVLBigRotateLeft(AVLNode* node)
{
    if (node == NULL)
        return node;

    if (node->right && GetDiff(node->right) < 0)
        node->right = AVLRotateRight(node->right);

    node = AVLRotateLeft(node);

    return node;
}

static inline AVLNode* AVLBigRotateRight(AVLNode* node)
{
    if (node == NULL)
        return node;

    if (node->left && GetDiff(node->left) > 0)
        node->left = AVLRotateLeft(node->left);

    node = AVLRotateRight(node);

    return node;
}

static inline AVLNode* AVLRotate(AVLNode* node)
{
    if (node == NULL)
        return node;

    if (AVLNeedRotateLeft(node))
        node = AVLBigRotateLeft(node);

    if (AVLNeedRotateRight(node))
        node = AVLBigRotateRight(node);

    return node;
}

AVLNode* AVLInsertNode(AVLNode* node, int key)
{
    if (node == NULL)
        return AVLNodeCtor(key);

    if (key == node->key)
        return node;

    if (key < node->key)
        node->left = AVLInsertNode(node->left, key);
    else
        node->right = AVLInsertNode(node->right, key);

    UpdateHeights(node);
    node = AVLRotate(node);

    return node;
}

void AVLInsert(AVL* tree, int key)
{
    assert(tree);

    tree->root = AVLInsertNode(tree->root, key);
}

AVLNode* AVLDeleteNode(AVLNode* node, int key)
{
    if (node == NULL)
        return NULL;
    
    AVLNode* retNode = NULL;

    if (key < node->key)
    {
        node->left = AVLDeleteNode(node->left, key);
        retNode = node;
    }
    else if (key > node->key)
    {
        node->right = AVLDeleteNode(node->right, key);
        retNode = node;
    }
    else 
    {   
        AVLNode* replacingNode = NULL;

        if (node->left == NULL)
            replacingNode = node->right;
        else if (node->right == NULL)
            replacingNode = node->left;
        else
        {
            node->left = UntieMaxNode(node->left, &replacingNode);
            
            replacingNode->left  = node->left;
            replacingNode->right = node->right;
        }

        AVLDtorOneNode(node);

        retNode = replacingNode;
    }

    UpdateHeights(retNode);
    retNode = AVLRotate(retNode);

    return retNode;
}

void AVLDelete(AVL* tree, int key)
{
    assert(tree);
    assert(tree->root);

    tree->root = AVLDeleteNode(tree->root, key);
}

static inline AVLNode* UntieMaxNode(AVLNode* root, AVLNode** maxNode)
{
    assert(root);
    assert(maxNode);

    if (root->right)
        root->right = UntieMaxNode(root->right, maxNode);
    else
    {
        *maxNode = root;
        
        AVLNode* retNode = root->left;
        root->left = NULL;

        return retNode;
    }

    UpdateHeights(root);
    root = AVLRotate(root);

    return root;
}
