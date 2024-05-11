#include "Testing.h"
#include "Sorts/HeapSort.h"

#include <stdio.h>

int main()
{
    //-----------------------Binary heap-------------------------------------------

    TestHeap("Tests/BinaryHeapTests", "TestsResults/BinaryHeap/Linear.out",    
                                            100000, 1000000, 100000, 1, HeapSortLinearBuild);
    TestHeap("Tests/BinaryHeapTests", "TestsResults/BinaryHeap/Inserts.out",
                                            100000, 1000000, 100000, 1, HeapSortInserts);
}