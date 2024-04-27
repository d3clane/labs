#ifndef AVL_H
#define AVL_H

#include <stddef.h>

typedef struct AVLNode
{
    int key;

    size_t subtreeHeight;

    struct AVLNode* left;
    struct AVLNode* right;
} AVLNode;

typedef struct AVL
{
    AVLNode* root;
} AVL;

AVLNode* AVLNodeCtor(int key);
AVL AVLCtor();
void AVLDtorOneNode(AVLNode* node);
void AVLDtorNodeRecursively(AVLNode* node);
void AVLDtor(AVL* tree);
void AVLNodeSetkey(AVLNode* node, int key);
void AVLNodeInit(AVLNode* node, int key);

AVLNode* AVLInsertNode(AVLNode* node, int key);
void AVLInsert(AVL* tree, int key);

AVLNode* AVLDeleteNode(AVLNode* node, int key);
void AVLDelete(AVL* tree, int key);

#endif