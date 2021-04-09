#include <iostream>
#include "../tests/tests.h"
#include "../include/utils.h"

int main() {
    tests::test_mergeSort();

    tests::test_quickSort();


    utils::date::convertTimestampToString(1617974105);

    std::cout << utils::date::convertTimestampToString(1617974105) << std::endl;

    return 0;
}
