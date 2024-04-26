#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct AVLNode
{
    int speed;

    size_t subtreeHeight;

    struct AVLNode* left;
    struct AVLNode* right;
} AVLNode;

typedef struct AVL
{
    AVLNode* root;
} AVL;

static inline size_t Max(size_t val1, size_t val2) { return val1 < val2 ? val2 : val1; }

AVLNode* AVLNodeCtor(int speed);
AVL AVLCtor();
void AVLDtorOneNode(AVLNode* node);
void AVLDtorNodeRecursively(AVLNode* node);
void AVLDtor(AVL* tree);
void AVLNodeSetSpeed(AVLNode* node, int speed);
void AVLNodeInit(AVLNode* node, int speed);

static inline bool AVLNeedRotateLeft(AVLNode* node);
static inline bool AVLNeedRotateRight(AVLNode* node);
static inline void UpdateHeights(AVLNode* node);
AVLNode* AVLRotateLeft(AVLNode* node);
AVLNode* AVLRotateRight(AVLNode* node);
static inline int GetDiff(AVLNode* node);

AVLNode* AVLBigRotateLeft(AVLNode* node);
AVLNode* AVLBigRotateRight(AVLNode* node);
AVLNode* AVLRotate(AVLNode* node);

AVLNode* AVLInsertNode(AVLNode* node, int speed);
void AVLInsert(AVL* tree, int speed);
AVLNode* AVLNext(AVL* tree, int speed);

static inline void EatLine();

AVLNode* AVLNodeCtor(int speed)
{
    AVLNode* node = (AVLNode*) calloc(1, sizeof(*node));
    assert(node);

    node->speed = speed;

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
    node->speed = 0;

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

void AVLNodeSetSpeed(AVLNode* node, int speed)
{
    assert(node);

    node->speed = speed;
}

void AVLNodeInit(AVLNode* node, int speed)
{
    assert(node);

    node->speed = speed;

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

AVLNode* AVLRotateLeft(AVLNode* node)
{
    AVLNode* tmp = node->right;
    node->right = tmp->left;
    tmp->left = node;

    UpdateHeights(node);
    UpdateHeights(tmp);

    return tmp;
}

AVLNode* AVLRotateRight(AVLNode* node)
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

AVLNode* AVLBigRotateLeft(AVLNode* node)
{
    if (node == NULL)
        return node;

    if (node->right && GetDiff(node->right) < 0)
        node->right = AVLRotateRight(node->right);

    node = AVLRotateLeft(node);

    return node;
}

AVLNode* AVLBigRotateRight(AVLNode* node)
{
    if (node == NULL)
        return node;

    if (node->left && GetDiff(node->left) > 0)
        node->left = AVLRotateLeft(node->left);

    node = AVLRotateRight(node);

    return node;
}

AVLNode* AVLRotate(AVLNode* node)
{
    if (node == NULL)
        return node;

    if (AVLNeedRotateLeft(node))
        node = AVLBigRotateLeft(node);

    if (AVLNeedRotateRight(node))
        node = AVLBigRotateRight(node);

    return node;
}

AVLNode* AVLInsertNode(AVLNode* node, int speed)
{
    if (node == NULL)
        return AVLNodeCtor(speed);

    //if (speed == node->speed)   // No insertion
    //    return node;

    if (speed < node->speed)
        node->left = AVLInsertNode(node->left, speed);
    else
        node->right = AVLInsertNode(node->right, speed);

    UpdateHeights(node);
    node = AVLRotate(node);

    return node;
}

void AVLInsert(AVL* tree, int speed)
{
    assert(tree);

    tree->root = AVLInsertNode(tree->root, speed);
}

AVLNode* AVLNext(AVL* tree, int speed)
{
    assert(tree);

    AVLNode* node = tree->root;

    AVLNode* bestRes = NULL;
    while (node)
    {
        if (speed == node->speed)
            return node;

        if (speed < node->speed)
        {
            bestRes = node;
            node = node->left;
        }
        else
            node = node->right;
    }

    return bestRes;
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

void ProcessAVLQueries()
{
    size_t n = 0;
    int scanfRes = scanf("%zu", &n);
    assert(scanfRes == 1);

    EatLine();

    AVL tree = AVLCtor();

    int prevRes = 0;

    srand(clock());

    while (n--)
    {
        char queryType = 0;
        int  speed     = 0;

        int scanfRes = scanf("%c%d", &queryType, &speed);
        assert(scanfRes == 2);

        switch (queryType)
        {
            case '+':
                AVLInsert(&tree, (speed + prevRes) % (int)1e9);
                prevRes = 0;
                break;
            case '?':
            {
                AVLNode* tmp = AVLNext(&tree, speed);

                if (tmp == NULL)
                    prevRes = -1;
                else
                    prevRes = tmp->speed;

                printf("%d\n", prevRes);

                break;
            }

            default:
                break;
        }

        EatLine();
    }

    AVLDtor(&tree);
}

int main()
{
    ProcessAVLQueries();
}
