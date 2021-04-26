#include "../include/exercises.h"


utils::stock::StockDayData* partI::loadStockData(utils::csv::CSVReader &reader) {
    struct utils::stock::StockDayData *data = new utils::stock::StockDayData[reader.getTotalRows() - 2];

    std::string* currLine;
    int index = 0;
    while (true) {

        // this will delete the previously allocated memory
        currLine = reader.getrow();
        if (currLine[0].empty()) break;
        data[index++] = {currLine[0],
                         std::stof(currLine[1]),
                         std::stof(currLine[2]),
                         std::stof(currLine[3]),
                         std::stof(currLine[4]),
                         std::stoi(currLine[5]),
                         (unsigned)std::stoi(currLine[6])};

        delete[] currLine;
    }

    return data;

}

void partI::exercise1(const std::string &fileName) {
    std::cout << "Running for file: " << fileName << std::endl;

    // create data reader and get data size
    utils::csv::CSVReader reader(fileName);
    int dataSize =  (int)reader.getTotalRows() - 2;

    // create array of structs containing data
    utils::stock::StockDayData* initialData = partI::loadStockData(reader);
    utils::stock::StockDayData* dataToSort = new utils::stock::StockDayData[dataSize];

    // run each algorithm multiple times
    // and get average runtime

    const int totalRuns = 100;
    int totalTime = 0;

    // merge sort
    for (int i = 0; i < totalRuns; ++i) {
        std::copy(initialData, initialData + dataSize, dataToSort);
        totalTime += (int)utils::timer::timeit<std::function<void()>>([dataToSort, dataSize]() {algo::mergeSort(dataToSort, 0, dataSize - 1);});
    }
    double averageMergeSortTime = ((double)totalTime) / totalRuns;
    std::cout << "Average merge sort time: " << averageMergeSortTime << "us" << std::endl;

    totalTime = 0;

    // quick sort
    for (int i = 0; i < totalRuns; ++i) {
        std::copy(initialData, initialData + dataSize, dataToSort);
        totalTime += (int)utils::timer::timeit<std::function<void()>>([dataToSort, dataSize]() {algo::quickSort(dataToSort, 0, dataSize - 1);});
    }

    double averageQuickSortTime = ((double)totalTime) / totalRuns;

    std::cout << "Average quick sort time: " << averageQuickSortTime << "us" << std::endl;

    delete[] initialData;
    delete[] dataToSort;

}

void partI::exercise2(const std::string &fileName) {
    std::cout << "Running for file: " << fileName << std::endl;

    // create data reader and get data size
    utils::csv::CSVReader reader(fileName);
    int dataSize =  (int)reader.getTotalRows() - 2;

    // create array of structs containing data
    utils::stock::StockDayData* initialData = partI::loadStockData(reader);
    utils::stock::StockDayData* dataToSort = new utils::stock::StockDayData[dataSize];

    // run each algorithm multiple times
    // and get average runtime

    const int totalRuns = 100;
    int totalTime = 0;

    //heap sort
    for (int i = 0; i < totalRuns; ++i) {
        std::copy(initialData, initialData + dataSize, dataToSort);
        totalTime += (int)utils::timer::timeit<std::function<void()>>([&dataToSort, dataSize]() {algo::heapSort(&dataToSort, dataSize);});
    }

    double averageHeapSortTime = ((double)totalTime) / totalRuns;

    std::cout << "Average heap sort time: " << averageHeapSortTime << "us" << std::endl;

    std::copy(initialData, initialData + dataSize, dataToSort);
    totalTime = 0;

    //counting sort
    for (int i = 0; i < totalRuns; ++i) {
        totalTime += (int)utils::timer::timeit<std::function<void()>>([dataToSort, dataSize]() {
            utils::stock::StockDayData *output = algo::countingSort(dataToSort, dataSize);
            delete[] output;
        });
    }

    double averageCountingSortTime = ((double)totalTime) / totalRuns;

    std::cout << "Average counting sort time: " << averageCountingSortTime << "us" << std::endl;

    delete[] initialData;
    delete[] dataToSort;
}

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
