#include <iostream>
#include "../tests/tests.h"
#include "../include/utils.h"

int main() {

    int arr[] = {1,2,3};

    std::cout << utils::array::compare<int>(arr, 3, arr, 3);

    return 0;
}
