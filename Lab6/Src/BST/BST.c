#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "BST.h"

static BSTNode* UntieMaxNode(BSTNode* root, BSTNode* prevNode);

BST BSTCtor()
{
    BST tree = 
    {
        tree.root = NULL,
    };

    return tree;
}

BSTNode* BSTNodeCtor()
{
    BSTNode* node = (BSTNode*)calloc(1, sizeof(*node));
    assert(node);

    node->key = 0;

    node->leftSon  = NULL;
    node->rightSon = NULL;

    return node;
}

BSTNode* BSTNodeInit(int key)
{
    BSTNode* node = BSTNodeCtor();

    node->key = key;

    return node;
}

void     BSTNodeDtor(BSTNode* node)
{
    if (node == NULL)
        return;

    node->key = 0;

    node->leftSon  = NULL;
    node->rightSon = NULL;

    free(node);
}

void     BSTSubTreeDtor(BSTNode* root)
{
    if (root == NULL)
        return;

    BSTSubTreeDtor(root->leftSon);
    BSTSubTreeDtor(root->rightSon);

    BSTNodeDtor(root);
}

void     BSTDtor(BST* tree)
{
    if (!tree || !tree->root)
        return;

    BSTSubTreeDtor(tree->root);
}

void BSTInsert(BST* tree, int key)
{
    assert(tree);

    BSTNode* newNode = BSTNodeInit(key);

    if (tree->root == NULL)
    {
        tree->root = newNode;
        return;
    }

    BSTNode* prevNode = NULL;
    BSTNode* node     = tree->root;

    while (node)
    {
        prevNode = node;
        if (key <= node->key)
            node = node->leftSon;
        else
            node = node->rightSon;
    }

    assert(prevNode);
    if (key <= prevNode->key)
        prevNode->leftSon = newNode;
    else
        prevNode->rightSon = newNode;
}

void BSTDelete(BST* tree, int key)
{
    assert(tree);

    BSTNode* prevNode = NULL;
    BSTNode* node     = tree->root;

    while (node)
    {
        if (node->key == key)
            break;

        prevNode = node;

        if (key <= node->key)
            node = node->leftSon;
        else 
            node = node->rightSon;
    }

    if (node == NULL)
        return;

    BSTNode* replacingNode = NULL;

    if (node->leftSon == NULL)
        replacingNode = node->rightSon;
    else if (node->rightSon == NULL)
        replacingNode = node->leftSon;
    else
    {
        replacingNode = UntieMaxNode(node->leftSon, node);
        
        replacingNode->leftSon  = node->leftSon;
        replacingNode->rightSon = node->rightSon;
    }

    if (!prevNode)
        tree->root = replacingNode;
    else
    {
        if (prevNode->leftSon == node)
            prevNode->leftSon  = replacingNode;
        else 
            prevNode->rightSon = replacingNode;
    }

    BSTNodeDtor(node);
}

static BSTNode* UntieMaxNode(BSTNode* root, BSTNode* rootPrevNode)
{
    assert(root);
    assert(rootPrevNode);

    BSTNode* prevNode = rootPrevNode;
    BSTNode* node     = root;

    while (node->rightSon)
    {
        prevNode = node;
        node     = node->rightSon;
    }

    if (prevNode->leftSon == node)
        prevNode->leftSon = NULL;
    else
        prevNode->rightSon = NULL;

    return node;
}
