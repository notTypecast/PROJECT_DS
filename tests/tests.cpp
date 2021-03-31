#include "tests.h"
#include "../include/algo.h"

void tests::test_mergeSort() {
    int initial[] = utils::array::duplicate(tests::unsorted, tests::UNSORTEDSIZE)

    algo::mergeSort(initial, 0, tests::UNSORTEDSIZE - 1);

    assert(utils::array::compare<int>(initial, tests::UNSORTEDSIZE, tests::expected, tests::UNSORTEDSIZE));

}

void tests::test_quickSort() {
    int initial[] = utils::array::duplicate(tests::unsorted, tests::UNSORTEDSIZE);

    algo::quickSort(initial, 0, tests::UNSORTEDSIZE - 1);

    assert(utils::array::compare<int>(initial, tests::UNSORTEDSIZE, tests::expected, tests::UNSORTEDSIZE));
}
