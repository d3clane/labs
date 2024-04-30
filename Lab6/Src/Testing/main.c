#include <assert.h>
#include <stdbool.h>

#include "Testing.h"

int main()
{
    const char* testsInsertsDir       = "Tests/Tests/Inserts";
    const char* testsDeletesDir       = "Tests/Tests/Deletes";
    const char* testsSortedDir        = "Tests/Tests/Sorted";

#define BST_DIR "BST/"
#define AVL_DIR "AVL/"
#define SPLAY_DIR "Splay/"
#define TREAP_DIR "Treap/"

#define INSERTS_DIR "Inserts.out"
#define DELETES_DIR "Deletes.out"
#define SORTED_DIR  "Sorted.out"

#define TESTS_RES_DIR "TestsResults/"

#if TREE_TYPE == BST_TYPE
    TestTree(testsInsertsDir, testsDeletesDir, TESTS_RES_DIR BST_DIR INSERTS_DIR,
             TESTS_RES_DIR BST_DIR DELETES_DIR, 
             100000, 100000, 1, 5, BSTCtor, BSTDtor, BSTInsert, BSTDelete);

    TestTree("Tests/Tests/Sorted/Inserts", "Tests/Tests/Sorted/Deletes", 
             TESTS_RES_DIR BST_DIR "SortedIns.out", TESTS_RES_DIR BST_DIR "SortedDel.out", 
             100000, 100000, 1, 5, BSTCtor, BSTDtor, BSTInsert, BSTDelete);
#elif TREE_TYPE == AVL_TYPE
    TestTree(testsInsertsDir, testsDeletesDir, TESTS_RES_DIR AVL_DIR INSERTS_DIR,
             TESTS_RES_DIR AVL_DIR DELETES_DIR, 
             100000, 1000000, 100000, 5, 
             AVLCtor, AVLDtor, AVLInsert, AVLDelete);

    TestTree("Tests/Tests/Sorted/Inserts", "Tests/Tests/Sorted/Deletes",
             TESTS_RES_DIR AVL_DIR "SortedIns.out", TESTS_RES_DIR AVL_DIR "SortedDel.out", 
             1000000, 1000000, 1, 5, 
             AVLCtor, AVLDtor, AVLInsert, AVLDelete);
#elif TREE_TYPE == TREAP_TYPE
    TestTree(testsInsertsDir, testsDeletesDir, TESTS_RES_DIR TREAP_DIR INSERTS_DIR,
            TESTS_RES_DIR TREAP_DIR DELETES_DIR, 
            100000, 1000000, 100000, 5, 
            TreapCtor, TreapDtor, TreapInsert, TreapDelete);
#elif TREE_TYPE == SPLAY_TYPE
    TestTree(testsInsertsDir, testsDeletesDir, TESTS_RES_DIR SPLAY_DIR INSERTS_DIR,
        TESTS_RES_DIR SPLAY_DIR DELETES_DIR, 
        100000, 1000000, 100000, 5, 
        SplayTreeCtor, SplayTreeDtor, SplayInsert, SplayDelete);
#else
    static_assert(false);
#endif
}