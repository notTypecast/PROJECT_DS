#include <iostream>
#include "../tests/tests.h"
#include "../include/utils.h"

int main() {
    tests::test_mergeSort();

    tests::test_quickSort();



    utils::csv::CSVReader reader("../data/agn.us.txt");
    std::size_t counter = 0;
	std::string *row;

	while (reader.getrow() != nullptr) {
		++counter;
	}

	std::cout << counter << std::endl;

    return 0;
}
