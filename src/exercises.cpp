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
            utils::stock::StockDayData *output = algo::countingSort(dataToSort, dataSize);
            for (int i = 0; i < dataSize; ++i) {
                std::cout << output[i].date << " " <<  output[i].close << std::endl;
            }
            delete[] output;
            exit(0);
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
    // get input date from user
    /*std::string inputDate;
    while (true) {
        std::cout << "Input date (YYYY-MM-DD): ";
        std::getline(std::cin, inputDate);

        // determine if input is valid date using regex, exit if it is
        if (std::regex_match(inputDate, std::regex(utils::regex::DATE))) {
            break;
        }

        std::cout << "Expected a valid date." << std::endl;
    }*/

    // read required data from file
    utils::csv::CSVReader reader("../data/agn.us.txt");
    int dataSize = (int) reader.getTotalRows() - 2;
    utils::stock::StockDayData *initialData = partI::loadStockData(reader);

    double totalAverageTimeBINARY = 0;
    double totalAverageTimeINTER = 0;

    for (int j = 0; j < dataSize; ++j) {
        std::string inputDate = initialData[j].date;
        // timing and getting average runtime works the same as it did with exercises 1 and 2
        const int totalRuns = 1000;
        int totalTime = 0;

        //binary search
        for (int i = 0; i < totalRuns; ++i) {
            totalTime += (int) utils::timer::timeit<std::function<void()>>(
                    [initialData, dataSize, inputDate]() {
                        algo::binarySearch(initialData, 0, dataSize - 1, inputDate);
                    });
        }

        double averageBinarySearchTime = ((double) totalTime) / totalRuns;
        totalAverageTimeBINARY += averageBinarySearchTime;

        totalTime = 0;

        //interpolation search
        for (int i = 0; i < totalRuns; ++i) {
            totalTime += (int) utils::timer::timeit<std::function<void()>>([initialData, dataSize, inputDate]() {
                algo::interpolationSearch(initialData, 0, dataSize - 1, inputDate);
            });
        }

        double averageInterpolationSearchTime = ((double) totalTime) / totalRuns;
        totalAverageTimeINTER += averageInterpolationSearchTime;
    }

    std::cout << "Binary search: " << totalAverageTimeBINARY / dataSize << "us" << std::endl;
    std::cout << "Interpolation search: " << totalAverageTimeINTER / dataSize << "us" << std::endl;

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

    test BIS;
    BIS.currentWorstTime = 0;
    test improvedBIS;
    improvedBIS.currentWorstTime = 0;

    for (int j = 0; j < (int)dataSize/10; ++j) {
        std::cout << "Running for: " << initialData[j].date << std::endl;
        std::string inputDate = initialData[j].date;

        const int totalRuns = 100000;
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

    std::cout << "BIS" << std::endl;
    std::cout << "Worst time: " << BIS.currentWorstTime << std::endl;
    std::cout << "For struct: ";
    utils::stock::printStockStruct(BIS.stockStruct);
    std::cout << std::endl;

    std::cout << "Improved BIS" << std::endl;
    std::cout << "Worst time: " << improvedBIS.currentWorstTime << std::endl;
    std::cout << "For struct: ";
    utils::stock::printStockStruct(improvedBIS.stockStruct);
    std::cout << std::endl;

    /*
    int volume = algo::binaryInterpolationSearch(initialData, dataSize, inputDate);
    std::cout << "Total volume for given date: " << volume << std::endl;*/

}
