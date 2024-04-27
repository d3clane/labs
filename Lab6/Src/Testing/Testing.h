#ifndef TESTING_H
#define TESTING_H

#include <stddef.h>

#include "AVL/AVL.h"
#include "BST/BST.h"
#include "Splay/Splay.h"
#include "Treap/Treap.h"

#if TREE_TYPE == BST_TYPE
typedef BST TreeType;
#elif TREE_TYPE == AVL_TYPE
typedef AVL TreeType;
#elif TREE_TYPE == SPLAY_TYPE
typedef SplayTree TreeType;
#elif TREE_TYPE == TREAP_TYPE
typedef Treap TreeType;
#else
static_assert(false);
#endif

void TestTree(const char* testsInsertsDir, const char* testsDeleteDir,
              const char* testsInsertsResDir, const char* testsDeletesResDir,
              size_t fromIns, size_t toIns, size_t stepIns, size_t numberOfTestsIns,
              TreeType (*Ctor)(), void (*Dtor)(TreeType* tree),
              void (*Insert)(TreeType* tree, int key), 
              void (*Delete)(TreeType* tree, int key));

#endif