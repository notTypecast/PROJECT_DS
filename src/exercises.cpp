#include "../include/exercises.h"

utils::stock::StockDayData *partI::loadStockData(utils::csv::CSVReader &reader) {
    // allocate memory to store data
    struct utils::stock::StockDayData *data = new utils::stock::StockDayData[reader.getTotalRows() - 2];

    std::string *currLine;
    int index = 0;
    while (true) {
        // read new line from file
        currLine = reader.getrow();
        // stop if empty line is found
        if (currLine[0].empty()) break;
        // save data to struct in array
        data[index++] = {currLine[0],
                         std::stof(currLine[1]),
                         std::stof(currLine[2]),
                         std::stof(currLine[3]),
                         std::stof(currLine[4]),
                         std::stoi(currLine[5]),
                         (unsigned) std::stoi(currLine[6])};

        // delete string array allocated for line
        delete[] currLine;
    }

    return data;

}

ds::HashTable<utils::stock::SDV_KeyDate> partII::loadStockDataToHashTable(utils::csv::CSVReader &reader) {
    // making sure M is odd
    // TODO: explain why 27 is the optimal M
    ds::HashTable<utils::stock::SDV_KeyDate> table(27);

    std::string *currLine;
    int index = 0;
    while (true) {
        // read new line from file
        currLine = reader.getrow();
        // stop if empty line is found
        if (currLine[0].empty()) break;
        // save data to struct in array
        utils::stock::SDV_KeyDate newEntry;
        newEntry.date = currLine[0];
        newEntry.volume = std::stoi(currLine[5]);
        table.insert(newEntry);
        // delete string array allocated for line
        delete[] currLine;
    }

    return table;
}

void partI::exercise1(const std::string &fileName) {
    std::cout << "Running for file: " << fileName << std::endl;

    // create data reader and get data size
    utils::csv::CSVReader reader(fileName);
    // each csv file has a row for the column names and an empty line at the end
    // we don't take these into account
    int dataSize = (int) reader.getTotalRows() - 2;

    // create array of structs containing data
    utils::stock::StockDayData *initialData = partI::loadStockData(reader);
    // dataToSort will be ay of initialData, to be used for algorithms that sort in-place
    // without this copy, we would have to load the data every time (significantly more I/O operations)
    utils::stock::StockDayData *dataToSort = new utils::stock::StockDayData[dataSize];

    // totalRuns: amount of times to run each algorithm on initialData
    // totalTime: total amount of time for all algorithm executions
    const int totalRuns = 100;
    int totalTime = 0;

    // merge sort
    for (int i = 0; i < totalRuns; ++i) {
        std::copy(initialData, initialData + dataSize, dataToSort);
        // add time spent on current execution to totalTime
        /*
         *
         * If we simply passed algo::mergeSort(...arguments), the function would be evaluated on the spot as an argument,
         * which is not desired, since we want the timeit util function to call it.
         * By simply passing the name algo::mergeSort as an argument, it wouldn't be possible to provide
         * arguments to the function.
         * As a result, it is necessary to pass a lambda which captures the context variables and calls the desired
         * function in its body, providing the captured variables as arguments.
         *
         */
        totalTime += (int) utils::timer::timeit < std::function < void() >> (
                [dataToSort, dataSize]() { algo::mergeSort(dataToSort, 0, dataSize - 1); });
    }
    // get average runtime
    double averageMergeSortTime = ((double) totalTime) / totalRuns;
    std::cout << "Average merge sort time: " << averageMergeSortTime << "us" << std::endl;

    // resetting the timer
    totalTime = 0;

    // quick sort
    for (int i = 0; i < totalRuns; ++i) {
        std::copy(initialData, initialData + dataSize, dataToSort);
        totalTime += (int) utils::timer::timeit < std::function < void() >> (
                [dataToSort, dataSize]() { algo::quickSort(dataToSort, 0, dataSize - 1); });
    }

    double averageQuickSortTime = ((double) totalTime) / totalRuns;

    std::cout << "Average quick sort time: " << averageQuickSortTime << "us" << std::endl;

    // free allocated memory
    delete[] initialData;
    delete[] dataToSort;

}

// this part does the same as partI::exercise1, but for heap sort and counting sort
// this works with close value instead of open value
void partI::exercise2(const std::string &fileName) {
    std::cout << "Running for file: " << fileName << std::endl;

    utils::csv::CSVReader reader(fileName);
    int dataSize = (int) reader.getTotalRows() - 2;

    utils::stock::StockDayData *initialData = partI::loadStockData(reader);
    utils::stock::StockDayData *dataToSort = new utils::stock::StockDayData[dataSize];

    const int totalRuns = 100;
    int totalTime = 0;

    //heap sort
    for (int i = 0; i < totalRuns; ++i) {
        std::copy(initialData, initialData + dataSize, dataToSort);
        totalTime += (int) utils::timer::timeit<std::function<void()>>(
                [&dataToSort, dataSize]() { algo::heapSort(&dataToSort, dataSize); });
    }

    double averageHeapSortTime = ((double) totalTime) / totalRuns;

    std::cout << "Average heap sort time: " << averageHeapSortTime << "us" << std::endl;

    std::copy(initialData, initialData + dataSize, dataToSort);
    totalTime = 0;

    //counting sort
    for (int i = 0; i < totalRuns; ++i) {
        totalTime += (int) utils::timer::timeit<std::function<void()>>([dataToSort, dataSize]() {
            delete[] algo::countingSort(dataToSort, dataSize);
        });
    }

    double averageCountingSortTime = ((double) totalTime) / totalRuns;

    std::cout << "Average counting sort time: " << averageCountingSortTime << "us" << std::endl;

    delete[] initialData;
    delete[] dataToSort;
}

/* For this part, we search for a given date using binary search and interpolation search
 * Both of these searching algorithms require the array to be searched to be sorted
 * Since the input data is sorted by dates, no further sorting is required after loading it
 */
void partI::exercise3() {
    std::string inputDate;

    while (true) {
        std::cout << "Input date (YYYY-MM-DD): ";
        std::getline(std::cin, inputDate);

        if (std::regex_match(inputDate, std::regex(utils::regex::DATE))) {
            break;
        }

        std::cout << "Expected a valid date." << std::endl;
    }

    utils::csv::CSVReader reader("../data/agn.us.txt");
    int dataSize =  (int)reader.getTotalRows() - 2;
    utils::stock::StockDayData* initialData = partI::loadStockData(reader);

    // dataset is sorted by dates (ascending) so we can perform binary search on array
    const int totalRuns = 1000;
    int totalTime = 0;

    //binary search
    for (int i = 0; i < totalRuns; ++i) {
        totalTime += (int)utils::timer::timeit<std::function<void()>>([initialData, dataSize, inputDate]() {algo::binarySearch(initialData, 0, dataSize - 1, inputDate);});
    }

    double averageBinarySearchTime = ((double)totalTime) / totalRuns;

    std::cout << "Average binary search time: " << averageBinarySearchTime << "us" << std::endl;

    totalTime = 0;

    //interpolation search
    for (int i = 0; i < totalRuns; ++i) {
        totalTime += (int)utils::timer::timeit<std::function<void()>>([initialData, dataSize, inputDate]() {algo::interpolationSearch(initialData, 0, dataSize - 1, inputDate);});
    }

    double averageInterpolationSearchTime = ((double)totalTime) / totalRuns;

    std::cout << "Average interpolation search time: " << averageInterpolationSearchTime << "us" << std::endl;

}

// Exercise 4 is the same as exercise 3, but it runs BIS and improved worst-case BIS instead
void partI::exercise4() {
    /*
    std::string inputDate;

    while (true) {
        std::cout << "Input date (YYYY-MM-DD): ";
        std::getline(std::cin, inputDate);

        if (std::regex_match(inputDate, std::regex(utils::regex::DATE))) {
            break;
        }

        std::cout << "Expected a valid date." << std::endl;
    }*/

    utils::csv::CSVReader reader("../data/agn.us.txt");
    int dataSize = (int) reader.getTotalRows() - 2;
    utils::stock::StockDayData *initialData = partI::loadStockData(reader);

    typedef struct {
        utils::stock::StockDayData stockStruct;
        double currentWorstTime;
    } test;

    double bistime = 0;
    double ibistime = 0;
    const int totalOutsideRuns = 100;

    for (int k = 0; k < totalOutsideRuns; ++k) {
        test BIS;
        BIS.currentWorstTime = 0;
        test improvedBIS;
        improvedBIS.currentWorstTime = 0;

        for (int j = 0; j < (int) dataSize; ++j) {
            std::string inputDate = initialData[j].date;

            const int totalRuns = 10;
            int totalTime = 0;

            // binary interpolation search
            for (int i = 0; i < totalRuns; ++i) {
                totalTime += (int) utils::timer::timeit<std::function<void()>>([initialData, dataSize, inputDate]() {
                    algo::binaryInterpolationSearch(initialData, dataSize, inputDate);
                });
            }

            double averageBinaryInterpolationSearchTime = ((double) totalTime) / totalRuns;
            if (averageBinaryInterpolationSearchTime > BIS.currentWorstTime) {
                BIS.currentWorstTime = averageBinaryInterpolationSearchTime;
                BIS.stockStruct = initialData[j];
            }

            totalTime = 0;

            // improved BIS
            for (int i = 0; i < totalRuns; ++i) {
                totalTime += (int) utils::timer::timeit<std::function<void()>>(
                        [initialData, dataSize, inputDate]() { algo::improvedBIS(initialData, dataSize, inputDate); });
            }

            double averageImprovedBISTime = ((double) totalTime) / totalRuns;
            if (averageImprovedBISTime > improvedBIS.currentWorstTime) {
                improvedBIS.currentWorstTime = averageImprovedBISTime;
                improvedBIS.stockStruct = initialData[j];
            }
        }
        bistime += BIS.currentWorstTime;
        ibistime += improvedBIS.currentWorstTime;
    }

    std::cout << "BIS" << std::endl;
    std::cout << "Average worst time: " << bistime / totalOutsideRuns << "us" << std::endl;

    std::cout << "Improved BIS" << std::endl;
    std::cout << "Average worst time: " << ibistime / totalOutsideRuns << "us" << std::endl;

    /*
    int volume = algo::binaryInterpolationSearch(initialData, dataSize, inputDate);
    std::cout << "Total volume for given date: " << volume << std::endl;*/

}

void partII::exercise1() {
    const std::string HELP = "─────────────────────────────────\n"
                             "Available commands:\n"
                             "-> print: Displays tree using in-order traversal.\n"
                             "-> search: Searches tree by date and returns volume.\n"
                             "-> edit: Edits volume for given date.\n"
                             "-> delete: Removes tree node for given date.\n"
                             "-> exit: Quits the menu.\n"
                             "─────────────────────────────────\n";

    utils::csv::CSVReader reader("../data/agn.us.txt");
    auto tree = partII::loadStockDataToAVLTree<utils::stock::SDV_KeyDate>(reader);

    std::string input;
    std::string input2;

    std::cout << HELP;

    while (true) {
        std::cout << ">> ";
        std::getline(std::cin, input);
        utils::string::lower(input);

        if (input == "exit") {
            break;
        }
        else if (input == "help") {
            std::cout << HELP;
        }
        else if (input == "print") {
            tree.printInOrder();
        }
        else if (input == "search" || input == "edit" || input == "delete") {
            std::cout << "Input date (YYYY-MM-DD): ";
            std::getline(std::cin, input2);
            if (std::regex_match(input2, std::regex(utils::regex::DATE))) {
                utils::stock::SDV_KeyDate acc;
                acc.date = input2;
                // this avl tree has unique keys, since there are no duplicate dates
                // therefore, no need to traverse linked list for same
                utils::stock::SDV_KeyDate *key;
                if (input != "delete") {
                    ds::LinkedKey<utils::stock::SDV_KeyDate> *linkedKey = tree.access(acc);
                    if (linkedKey == nullptr) {
                        std::cout << "Date not found." << std::endl;
                        continue;
                    }
                    key = linkedKey->key;
                    // deleting LinkedKey object since it was created only to be returned
                    delete linkedKey;
                }
                if (input == "search") {
                    std::cout << "Volume for " << input << ": " << key->volume << std::endl;
                }
                else if (input == "edit"){
                    while (true) {
                        std::cout << "New volume: ";
                        std::getline(std::cin, input2);
                        try {
                            int newVolume = std::stoi(input2);
                            if (newVolume < 0) {
                                throw std::invalid_argument("Must be non-negative.");
                            }
                            key->volume = newVolume;
                            break;
                        }
                        catch (const std::invalid_argument& exc) {
                            std::cout << "Expected a non-negative integer." << std::endl;
                        }
                    }
                }
                else if (input == "delete") {
                    if (tree.remove(acc)) {
                        std::cout << "Successfully deleted entry." << std::endl;
                    }
                    else {
                        std::cout << "Entry not found." << std::endl;
                    }
                }
            }
            else {
                std::cout << "Invalid date. Must be YYYY-MM-DD." << std::endl;
            }

        }
        else {
            std::cout << "Unknown command. Type help for a list of commands." << std::endl;
        }
    }
}

void partII::exercise2() {
    const std::string HELP = "─────────────────────────────────\n"
                             "Available commands:\n"
                             "-> print: Displays tree using in-order traversal.\n"
                             "-> max: Get date(s) with maximum trade volume.\n"
                             "-> min: Get date(s) with minimum trade volume.\n"
                             "-> exit: Quits the menu.\n"
                             "─────────────────────────────────\n";

    utils::csv::CSVReader reader("../data/agn.us.txt");
    auto tree = partII::loadStockDataToAVLTree<utils::stock::SDV_KeyVolume>(reader);

    std::string input;

    std::cout << HELP;

    while (true) {
        std::cout << ">> ";
        std::getline(std::cin, input);
        utils::string::lower(input);

        if (input == "exit") {
            break;
        }
        else if (input == "help") {
            std::cout << HELP;
        }
        else if (input == "print") {
            tree.printInOrder();
        }
        else if (input == "max") {
            ds::LinkedKey<utils::stock::SDV_KeyVolume> *maxKey = tree.getMaxKey();
            std::cout << "Date(s) with volume " << maxKey->key->volume << " (maximum): ";
            while (maxKey != nullptr) {
                std::cout << maxKey->key->date << " ";
                maxKey = maxKey->next;
            }
            std::cout << std::endl;
        }
        else if (input == "min") {
            ds::LinkedKey<utils::stock::SDV_KeyVolume> *minKey = tree.getMinKey();
            std::cout << "Date(s) with volume " << minKey->key->volume << " (minimum): ";
            while (minKey != nullptr) {
                std::cout << minKey->key->date << " ";
                minKey = minKey->next;
            }
            std::cout << std::endl;
        }
        else {
            std::cout << "Unknown command. Type help for a list of commands." << std::endl;
        }
    }

}

void partII::exercise3() {
    const std::string HELP = "─────────────────────────────────\n"
                             "Available commands:\n"
                             "-> print: Displays tree using in-order traversal.\n"
                             "-> search: Searches tree by date and returns volume.\n"
                             "-> edit: Edits volume for given date.\n"
                             "-> delete: Removes tree node for given date.\n"
                             "-> exit: Quits the menu.\n"
                             "─────────────────────────────────\n";

    utils::csv::CSVReader reader("../data/agn.us.txt");
    auto table = partII::loadStockDataToHashTable(reader);

    std::string input;
    std::string input2;

    std::cout << HELP;

    while (true) {
        std::cout << ">> ";
        std::getline(std::cin, input);
        utils::string::lower(input);

        if (input == "exit") {
            break;
        }
        else if (input == "help") {
            std::cout << HELP;
        }
        else if (input == "print") {
            table.print();
        }
        else if (input == "search" || input == "edit" || input == "delete") {
            std::cout << "Input date (YYYY-MM-DD): ";
            std::getline(std::cin, input2);
            if (std::regex_match(input2, std::regex(utils::regex::DATE))) {
                utils::stock::SDV_KeyDate acc;
                acc.date = input2;
                // there are no duplicate dates, since this is a hash table
                // therefore, no need to traverse linked list for same
                utils::stock::SDV_KeyDate *key;
                if (input != "delete") {
                    ds::LinkedKey<utils::stock::SDV_KeyDate> *linkedKey = table.access(acc);
                    if (linkedKey == nullptr) {
                        std::cout << "Date not found." << std::endl;
                        continue;
                    }
                    key = linkedKey->key;
                }
                if (input == "search") {
                    std::cout << "Volume for " << input << ": " << key->volume << std::endl;
                }
                else if (input == "edit"){
                    while (true) {
                        std::cout << "New volume: ";
                        std::getline(std::cin, input2);
                        try {
                            int newVolume = std::stoi(input2);
                            if (newVolume < 0) {
                                throw std::invalid_argument("Must be non-negative.");
                            }
                            key->volume = newVolume;
                            break;
                        }
                        catch (const std::invalid_argument& exc) {
                            std::cout << "Expected a non-negative integer." << std::endl;
                        }
                    }
                }
                else if (input == "delete") {
                    if (table.remove(acc)) {
                        std::cout << "Successfully deleted entry." << std::endl;
                    }
                    else {
                        std::cout << "Entry not found." << std::endl;
                    }
                }
            }
            else {
                std::cout << "Invalid date. Must be YYYY-MM-DD." << std::endl;
            }
        }
        else {
            std::cout << "Unknown command. Type help for a list of commands." << std::endl;
        }
    }

}

void partII::run() {
    std::string input;

    while (true) {
        std::cout << "Load data using a binary search tree or a hash table? (BST/HT)" << std::endl << "> ";
        std::getline(std::cin, input);
        utils::string::lower(input);

        if (input == "bst") {
            while (true) {
                std::cout << "Sort based on dates or volume? (D/V)" << std::endl << "> ";
                std::getline(std::cin, input);
                utils::string::lower(input);

                if (input == "d") {
                    partII::exercise1();
                }
                else if (input == "v") {
                    partII::exercise2();
                }
                else if (input == "back") {
                    break;
                }
                else {
                    std::cout << "Unrecognized option. Expected D or V." << std::endl;
                    continue;
                }
                break;
            }
        }
        else if (input == "ht") {
            exercise3();
        }
        else if (input == "exit") {
            break;
        }
        else {
            std::cout << "Unrecognized option. Expected BST or HT." << std::endl;
            continue;
        }
    }
}
