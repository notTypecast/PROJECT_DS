#include <iostream>
#include "../include/utils.h"

int main() {
    utils::csv::CSVReader reader("../data/agn.us.txt");
    std::cout << reader.getTotalRows() << std::endl;

    std::string *row = reader.getrow();
    std::cout << row[0] << std::endl;

    return 0;
}
