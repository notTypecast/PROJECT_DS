#include <iostream>
#include "../include/utils.h"
#include "../include/exercises.h"

int main() {
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

    return 0;
}
