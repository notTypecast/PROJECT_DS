#include <cassert>
#include "../include/utils.h"
#ifndef TESTS_H
#define TESTS_H

namespace tests {
    const int unsorted[] = {5, 1, 0, 18, 4, 7};
    const int UNSORTEDSIZE = 6;

    const int expected[] = {0, 1, 4, 5, 7, 18};

    void test_mergeSort();
    void test_quickSort();
}

#endif
