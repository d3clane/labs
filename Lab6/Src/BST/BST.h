#ifndef BST_H
#define BST_H

typedef struct BSTNode
{
    int key;

    struct BSTNode* leftSon;
    struct BSTNode* rightSon;
} BSTNode;

typedef struct BST
{
    BSTNode* root;
} BST;

BSTNode* BSTNodeCtor();
BSTNode* BSTNodeInit(int key);

BST BSTCtor();

void     BSTNodeDtor(BSTNode* node);
void     BSTSubTreeDtor(BSTNode* root);
void     BSTDtor(BST* tree);

void BSTInsert(BST* tree, int key);
void BSTDelete(BST* tree, int key);

#endif