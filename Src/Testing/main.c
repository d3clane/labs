#include "Testing.h"
#include "Sorts/Sorts.h"

int main()
{
    TestSort("Tests/small_tests", "TestsResults/Point1/Bubble.out",    
                                            0, 1000, 50, 5, BubbleSort   );
    TestSort("Tests/small_tests", "TestsResults/Point1/Insertion.out", 
                                            0, 1000, 50, 5, InsertionSort);
    TestSort("Tests/small_tests", "TestsResults/Point1/Selection.out", 
                                            0, 1000, 50, 5, SelectionSort);
    TestSort("Tests/small_tests", "TestsResults/Point1/Shell.out", 
                                            0, 1000, 50, 5, ShellSort    );
}