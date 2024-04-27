#ifndef TESTING_H
#define TESTING_H

#include <stddef.h>

#include "AVL/AVL.h"
#include "BST/BST.h"
#include "Splay/Splay.h"
#include "Treap/Treap.h"

#if TREE_TYPE == BST
typedef BST TreeType;
#elif TREE_TYPE == AVL
typedef AVL TreeType;
#elif TREE_TYPE == SPLAY
typedef Splay TreeType;
#elif TREE_TYPE == Treap
typedef Treap TreeType;
#else
static_assert(false);
#endif

void TestTree(const char* testsInsertsDir, const char* testsDeleteDir,
              const char* testsInsertsResFileName, const char* testsDeletesResFileName,
              size_t fromIns, size_t toIns, size_t stepIns, size_t numberOfTestsIns,
              size_t fromDel, size_t toDel, size_t stepDel, size_t numberOfTestsDel,
              TreeType (*Ctor)(), void (*Dtor)(TreeType* tree),
              void (*Insert)(TreeType* tree, int key), 
              void (*Delete)(TreeType* tree, int key));
              
#endif