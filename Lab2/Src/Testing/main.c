#include "Testing.h"
#include "Sorts/Sorts.h"

int main()
{
    //-----------------------Point 1-------------------------------------------

    TestSort("Tests/small_tests", "TestsResults/Point1/Bubble.out",    
                                            0, 1000, 50, 5, BubbleSort   );
    TestSort("Tests/small_tests", "TestsResults/Point1/Insertion.out", 
                                            0, 1000, 50, 5, InsertionSort);
    TestSort("Tests/small_tests", "TestsResults/Point1/Selection.out", 
                                            0, 1000, 50, 5, SelectionSort);
    TestSort("Tests/small_tests", "TestsResults/Point1/Shell.out", 
                                            0, 1000, 50, 5, ShellSort    );

    //-----------------------Point 2-------------------------------------------

    TestHeapSort("Tests/big_tests", "TestsResults/Point2/HeapSortTestRank", 
                                            0, 1000000, 10000, 1, HeapSortTestRank);

    //-----------------------Point 3-------------------------------------------
    
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

    //-----------------------Point 6-------------------------------------------

    TestSort("Tests/very_small_tests", "TestsResults/Point6/HoareCenter.out", 
                                            1, 150, 1, 5, QsortHoare);
    TestSort("Tests/very_small_tests", "TestsResults/Point6/Shell.out", 
                                            1, 150, 1, 5, ShellSort);

    //-----------------------Point 7-------------------------------------------

    TestIntroSort("Tests/big_tests", "TestsResults/Point7/TestingDepth.out",
                                            0, 1000000, 10000, 1, IntroSortTestConstant);

    TestSort("Tests/big_tests", "TestsResults/Point7/IntroSort.out",
                                              0, 1000000, 10000, 1, IntroSort);

    TestSort("Tests/big_tests", "TestsResults/Point7/QuickSort.out",
                                            0, 1000000, 10000, 1, QsortHoare);

    //-----------------------Point 8-------------------------------------------

    TestSort("Tests/big_tests", "TestsResults/Point8/LSD.out", 
                                            0, 1000000, 10000, 1, LSDSort);
    TestSort("Tests/big_tests", "TestsResults/Point8/MSD.out", 
                                            0, 1000000, 10000, 1, MSDSort);
    
   //-----------------------Point 9-------------------------------------------

    TestSort("Tests/big_tests", "TestsResults/Point9/HeapSort.out",
                                            0, 1000000, 10000, 1, HeapSort);

    TestSort("Tests/big_tests", "TestsResults/Point9/MergeIterative.out",
                                            0, 1000000, 10000, 1, IterativeMergeSort);

    TestSort("Tests/big_tests", "TestsResults/Point9/Hoare_Central.out",
                                            0, 1000000, 10000, 1, QsortHoare);

    TestSort("Tests/big_tests", "TestsResults/Point9/Introsort.out",
                                            0, 1000000, 10000, 1, IntroSort);

    TestSort("Tests/big_tests", "TestsResults/Point9/LSD.out",
                                            0, 1000000, 10000, 1, LSDSort);

    TestSort("Tests/big_tests", "TestsResults/Point9/QsortStd.out",
                                            0, 1000000, 10000, 1, QsortStd);
}