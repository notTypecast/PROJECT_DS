#include <iostream>
#include "../include/utils.h"
#include "../include/exercises.h"
#include "../include/algo.h"
#include "../include/ds.h"

int main() {
    /*
    std::string input;

    while (true) {
        std::cout << "Part I or II? (1/2)" << std::endl << "> ";
        std::getline(std::cin, input);
        utils::string::lower(input);

        if (input == "1") {
            std::cout << "Exercise 1" << std::endl << "─────────────────────────────────" << std::endl;
            partI::exercise1("../data/agn.us.txt");
            partI::exercise1("../data/ainv.us.txt");
            partI::exercise1("../data/ale.us.txt");
            std::cout << "─────────────────────────────────" << std::endl;

            std::cout << "Exercise 2" << std::endl << "─────────────────────────────────" << std::endl;
            partI::exercise2("../data/agn.us.txt");
            partI::exercise2("../data/ainv.us.txt");
            partI::exercise2("../data/ale.us.txt");
            std::cout << "─────────────────────────────────" << std::endl;

            std::cout << "Exercise 3" << std::endl << "─────────────────────────────────" << std::endl;
            partI::exercise3();
            std::cout << "─────────────────────────────────" << std::endl;

            std::cout << "Exercise 4" << std::endl << "─────────────────────────────────" << std::endl;
            partI::exercise4();
            std::cout << "─────────────────────────────────" << std::endl;
        }
        else if (input == "2") {
            partII::run();
        }
        else {
            std::cout << "Expected 1 or 2." << std::endl;
            continue;
        }
        break;
    }
    */
    std::string element = "2009-08-05";
    /*
    utils::csv::CSVReader reader("../data/agn.us.txt");
    int dataSize = (int) reader.getTotalRows() - 2;
    utils::stock::StockDayData *initialData = partI::loadStockData(reader);
    std::cout << (int) utils::timer::timeit<std::function<void()>>([initialData, dataSize, element]() {
        algo::binarySearch(initialData, 0, dataSize - 1, element);
    }) << std::endl;
    std::cout << (int) utils::timer::timeit<std::function<void()>>([initialData, dataSize, element]() {
        algo::interpolationSearch(initialData, 0, dataSize - 1, element);
    }) << std::endl;

    delete[] initialData;*/
    partI::exercise4();
    /*
    std::cout << (int) utils::timer::timeit<std::function<void()>>([element]() {
        std::string test = "2005";

        int current = 0;
        int str_size = (int) test.length();
        for (int i = 0; i < str_size; ++i) {
            current += (test.at(i) - 48) * (int) pow(10, str_size - 1 - i);
        }
        //std::cout << current << std::endl;

        //int date = std::stoi("2005");

    }) << std::endl;
     */

    return 0;
}
