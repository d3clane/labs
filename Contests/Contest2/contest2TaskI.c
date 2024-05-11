#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct SplayNode
{
    char* key;

    char* val;

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
SplayNode* SplayNodeCtor(const char* key, const char* val);
void SplayOneNodeDtor(SplayNode* node);
void SplayDtor(SplayNode* node);

SplayNode* GetParent(SplayNode* node);
SplayNode* GetGrandParent(SplayNode* node);

static inline void RotateLeft(SplayNode* node);
static inline void RotateRight(SplayNode* node);

SplayNodesPair SplayNodesPairCtor(SplayNode* node1, SplayNode* node2);

static void Splay(SplayNode* node);
static SplayNodesPair Split(SplayNode* tree, const char* key);
void Insert(SplayTree* tree, const char* key, const char* val);
SplayNode* Find(SplayTree* tree, const char* key);

SplayTree SplayTreeCtor()
{
    SplayTree tree =
            {
                    .root = NULL,
            };

    return tree;
}

SplayNode* SplayNodeCtor(const char* key, const char* val)
{
    SplayNode* node = (SplayNode*) calloc(1, sizeof(*node));
    assert(node);

    node->key = strdup(key);
    node->val = strdup(val);

    node->left = node->right = node->parent = NULL;

    return node;
}

void SplayOneNodeDtor(SplayNode* node)
{
    free(node->key);
    free(node->val);

    node->key = NULL;
    node->val = NULL;

    node->left = node->right = node->parent = NULL;

    free(node);
}

void SplayDtor(SplayNode* node)
{
    if (node == NULL)
        return;

    SplayDtor(node->left);
    SplayDtor(node->right);
    SplayOneNodeDtor(node);
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

static SplayNodesPair Split(SplayNode* tree, const char* key)
{
    SplayNode* node = tree;
    SplayNode* nearestNode = NULL;

    while (node)
    {
        int cmpRes = strcmp(key, node->key);

        if (cmpRes == 0)
        {
            nearestNode = node;
            break;
        }

        if (cmpRes < 0)
        {
            node = node->left;
        } else
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

void Insert(SplayTree* tree, const char* key, const char* val)
{
    SplayNodesPair pair = Split(tree->root, key);

    SplayNode* newNode = SplayNodeCtor(key, val);

    newNode->left = pair.node1;
    if (pair.node1) pair.node1->parent = newNode;

    newNode->right = pair.node2;
    if (pair.node2) pair.node2->parent = newNode;

    tree->root = newNode;
}

SplayNode* Find(SplayTree* tree, const char* key)
{
    SplayNode* node = tree->root;

    SplayNode* prevNode = NULL;
    while (node)
    {
        prevNode = node;
        int cmpRes = strcmp(key, node->key);

        if (cmpRes == 0)
            break;

        if (cmpRes < 0)
            node = node->left;
        else
            node = node->right;
    }

    // if key == node.key -> prevNode == node
    Splay(prevNode);

    if (node) tree->root = node;

    return node;
}

static inline void EatLine()
{

    while (true)
    {
        int ch = getchar();

        if (ch == EOF || ch == '\n')
            break;
    }
}

void ProcessNamesQueries()
{
    SplayTree treeNames = SplayTreeCtor();
    SplayTree treeCallSigns = SplayTreeCtor();

    size_t n = 0;
    int scanfRes = scanf("%zu", &n);
    EatLine();
    assert(scanfRes == 1);

    char* name     = NULL;
    char* callSign = NULL;
    while (n--)
    {
        size_t nameBufLen = 0;
        int readRes = getdelim(&name, &nameBufLen, ' ', stdin);
        name[strlen(name) - 1] = '\0';
        assert(readRes != -1);

        readRes     = getline(&callSign, &nameBufLen, stdin);
        callSign[strlen(callSign) - 1] = '\0';
        assert(readRes != -1);

        Insert(&treeNames, name, callSign);
        Insert(&treeCallSigns, callSign, name);

        free(name);
        free(callSign);
        name     = NULL;
        callSign = NULL;
    }

    size_t q = 0;
    scanfRes = scanf("%zu", &q);
    EatLine();
    assert(scanfRes == 1);

    while (q--)
    {
        size_t nameBufLen = 0;
        int readRes = getline(&name, &nameBufLen, stdin);
        name[strlen(name) - 1] = '\0';
        assert(readRes != -1);

        SplayNode* findRes = Find(&treeNames, name);

        if (findRes == NULL)
            findRes = Find(&treeCallSigns, name);

        assert(findRes);

        printf("%s\n", findRes->val);

        free(name);
        name = NULL;
    }

    SplayDtor(treeNames.root);
    SplayDtor(treeCallSigns.root);
}

int main()
{
    ProcessNamesQueries();
}
