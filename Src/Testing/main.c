#include "Testing.h"
#include "Sorts/Sorts.h"

#include <stdio.h>

int main()
{
    
    /*
    //-----------------------Point 1-------------------------------------------
    TestSort("Tests/small_tests", "TestsResults/Point1/Bubble.out",    
                                            0, 1000, 50, 5, BubbleSort   );
    TestSort("Tests/small_tests", "TestsResults/Point1/Insertion.out", 
                                            0, 1000, 50, 5, InsertionSort);
    TestSort("Tests/small_tests", "TestsResults/Point1/Selection.out", 
                                            0, 1000, 50, 5, SelectionSort);
    TestSort("Tests/small_tests", "TestsResults/Point1/Shell.out", 
                                            0, 1000, 50, 5, ShellSort    );

    
    */

    //-----------------------Point 2-------------------------------------------

    TestHeapSort("Tests/big_tests", "TestsResults/Point2/HeapSort", 
                                            0, 1000000, 10000, 1, HeapSort);

    //-----------------------Point 3-------------------------------------------
    
    /*
    
    TestSort("Tests/big_tests", "TestsResults/Point3/RecursiveMerge.out", 
                                            0, 1000000, 10000, 1, RecursiveMergeSort);
    TestSort("Tests/big_tests", "TestsResults/Point3/IterativeMerge.out", 
                                            0, 1000000, 10000, 1, IterativeMergeSort);
    

    //-----------------------Point 4-------------------------------------------

    
    TestSort("Tests/big_tests", "TestsResults/Point4/Lomuto_big_tests.out", 
                                            0, 1000000, 10000, 1, QsortLomuto);
    TestSort("Tests/big_tests", "TestsResults/Point4/Hoare_big_tests.out", 
                                            0, 1000000, 10000, 1, QsortHoare);

    TestSort("Tests/big_tests", "TestsResults/Point4/Ternary_big_tests.out", 
                                            0, 1000000, 10000, 1, QsortTernary);

    

    TestSort("Tests/test_most_duplicates", "TestsResults/Point4/Lomuto_duplicates_tests.out", 
                                            0, 1000000, 10000, 1, QsortLomuto);
    TestSort("Tests/test_most_duplicates", "TestsResults/Point4/Hoare_duplicates_tests.out", 
                                            0, 1000000, 10000, 1, QsortHoare);

    TestSort("Tests/test_most_duplicates", "TestsResults/Point4/Ternary_duplicates_tests.out", 
                                            0, 1000000, 10000, 1, QsortTernary);

    

    TestSort("Tests/big_tests", "TestsResults/Point4/OneBranch_big_tests.out", 
                                            0, 1000000, 10000, 1, QsortOneBranch);

    

    //-----------------------Point 5-------------------------------------------

    
    TestSort("Tests/big_tests", "TestsResults/Point5/HoareCenter.out", 
                                            0, 1000000, 10000, 1, QsortHoare);
    TestSort("Tests/big_tests", "TestsResults/Point5/HoareRnd.out", 
                                            0, 1000000, 10000, 1, QsortRndPivot);

    TestSort("Tests/big_tests", "TestsResults/Point5/HoareMedian3.out", 
                                            0, 1000000, 10000, 1, QsortMedian3Pivot); 
    TestSort("Tests/big_tests", "TestsResults/Point5/HoareMedianRnd3.out", 
                                            0, 1000000, 10000, 1, QsortMedianRnd3Pivot); 

    

   //-----------------------Point 8-------------------------------------------

    
    TestSort("Tests/big_tests", "TestsResults/Point8/LSD.out", 
                                            0, 1000000, 10000, 1, LSDSort);
    TestSort("Tests/big_tests", "TestsResults/Point8/MSD.out", 
                                            0, 1000000, 10000, 1, MSDSort);
    
    
    */
   
    //TODO: сука все перемерить где после point 2 там делил не на то
}