#include "tests.h"
#include "../include/algo.h"


void tests::test_mergeSort() {
    int unsorted[] = {5, 1, 0, 18, 4, 7};
    int expected[] = {0, 1, 4, 5, 7, 18};

    algo::mergeSort(unsorted, 0, 5);

}
