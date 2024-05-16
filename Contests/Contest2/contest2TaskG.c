#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct TreapNode
{
    int key;
    int priority;

    size_t subtreeSize;

    struct TreapNode* leftSon;
    struct TreapNode* rightSon;
} TreapNode;

typedef struct Treap
{
    TreapNode* root;
} Treap;

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

static inline void UpdateSize(TreapNode* tree);

static TreapNodesPair Split(TreapNode* tree, int key);
static TreapNode* Merge(TreapNode* tree1, TreapNode* tree2);

static TreapNode* FindKey(TreapNode* tree, int key);
static TreapNode* GetMinValNode(TreapNode* tree);

bool Exist(Treap* treap, int key);
void Insert(Treap* treap, int key);
void Delete(Treap* treap, int key);
TreapNode* Next(Treap* treap, int key);
TreapNode* Prev(Treap* treap, int key);
TreapNode* KthNodeRecursiveCall(TreapNode* node, size_t k);
TreapNode* KthNode(Treap* treap, size_t k);

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

    treapNode->subtreeSize = 1;
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

    node->subtreeSize = 0;

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

static inline void UpdateSize(TreapNode* tree)
{
    if (tree == NULL)
        return;

    size_t leftSubtreeSize  = tree->leftSon  ? tree->leftSon->subtreeSize  : 0;
    size_t rightSubtreeSize = tree->rightSon ? tree->rightSon->subtreeSize : 0;

    tree->subtreeSize = leftSubtreeSize + rightSubtreeSize + 1;
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
        UpdateSize(tree);
        return TreapNodesPairCtor(pair.node1, tree);
    } else
    {
        pair = Split(tree->rightSon, key);
        tree->rightSon = pair.node1;
        UpdateSize(tree);
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
        UpdateSize(tree2);
        return tree2;
    } else
    {
        tree1->rightSon = Merge(tree1->rightSon, tree2);
        UpdateSize(tree1);
        return tree1;
    }
}

static TreapNode* FindKey(TreapNode* tree, int key)
{
    TreapNode* node = tree;
    while (node && node->key != key)
    {
        if (key < node->key)
            node = node->leftSon;
        else
            node = node->rightSon;
    }

    return node;
}

static TreapNode* GetMaxValNode(TreapNode* tree)
{
    if (tree == NULL)
        return tree;

    TreapNode* node = tree;
    while (node->rightSon)
        node = node->rightSon;

    return node;
}

static TreapNode* GetMinValNode(TreapNode* tree)
{
    if (tree == NULL)
        return tree;

    TreapNode* node = tree;
    while (node->leftSon)
        node = node->leftSon;

    return node;
}

bool Exist(Treap* treap, int key)
{
    return FindKey(treap->root, key) != NULL;
}

void Insert(Treap* treap, int key)
{
    assert(treap);

    if (Exist(treap, key))
        return;

    TreapNodesPair pair = Split(treap->root, key);
    treap->root = Merge(Merge(pair.node1, TreapNodeCtor(key)), pair.node2);
}

void Delete(Treap* treap, int key)
{
    assert(treap);

    TreapNodesPair pair1 = Split(treap->root, key - 1);
    TreapNodesPair pair2 = Split(pair1.node2, key);

    TreapDtorRecursively(pair2.node1);

    treap->root = Merge(pair1.node1, pair2.node2);
}

TreapNode* Next(Treap* treap, int key)
{
    assert(treap);

    TreapNodesPair pair = Split(treap->root, key);

    TreapNode* minValNode = GetMinValNode(pair.node2);

    treap->root = Merge(pair.node1, pair.node2);

    return minValNode;
}

TreapNode* Prev(Treap* treap, int key)
{
    assert(treap);

    TreapNodesPair pair = Split(treap->root, key);

    TreapNode* minValNode = GetMaxValNode(pair.node1);

    treap->root = Merge(pair.node1, pair.node2);

    return minValNode;
}

TreapNode* KthNodeRecursiveCall(TreapNode* node, size_t k)
{
    if (node == NULL)
        return NULL;

    size_t leftSubtreeSize  = node->leftSon  ? node->leftSon->subtreeSize  : 0;

    if (k == leftSubtreeSize + 1)
        return node;
    else if (k <= leftSubtreeSize)
        return KthNodeRecursiveCall(node->leftSon, k);
    else
        return KthNodeRecursiveCall(node->rightSon, k - leftSubtreeSize - 1);
}

TreapNode* KthNode(Treap* treap, size_t k)
{
    assert(treap);

    return KthNodeRecursiveCall(treap->root, k + 1);
}

void ProcessTreapQueries(Treap* treap)
{
#define MAX_COMMAND_LEN 20
#define MAX_COMMAND_LEN_FORMAT_STR "%19s"

    char command[MAX_COMMAND_LEN] = "";
    int val = 0;
    while (scanf(MAX_COMMAND_LEN_FORMAT_STR "%d", command, &val) != EOF)
    {
        if (strcmp(command, "insert") == 0)
            Insert(treap, val);
        else if (strcmp(command, "delete") == 0)
            Delete(treap, val);
        else if (strcmp(command, "exists") == 0)
        {
            if (Exist(treap, val))
                printf("true\n");
            else
                printf("false\n");
        }
        else if (strcmp(command, "next") == 0)
        {
            TreapNode* next = Next(treap, val);

            if (next == NULL)
                printf("none\n");
            else
                printf("%d\n", next->key);
        }
        else if (strcmp(command, "prev") == 0)
        {
            TreapNode* prev = Prev(treap, val);

            if (prev == NULL)
                printf("none\n");
            else
                printf("%d\n", prev->key);
        }
        else if (strcmp(command, "kth")  == 0)
        {
            TreapNode* kthNode = KthNode(treap, val);

            if (kthNode == NULL)
                printf("none\n");
            else
                printf("%d\n", kthNode->key);
        }
    }

#undef MAX_COMMAND_LEN
#undef MAX_COMMAND_LEN_FORMAT_STR    
}

int main()
{
    srand(15);

    Treap treap = TreapCtor();

    ProcessTreapQueries(&treap);

    TreapDtor(&treap);
}
