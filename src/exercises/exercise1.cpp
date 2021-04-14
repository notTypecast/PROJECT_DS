#include "../../include/exercises.h"


void partI::exercise1(const std::string &fileName) {
    // create data reader and get data size
    utils::csv::CSVReader reader(fileName);
    int dataSize =  (int)reader.getTotalRows() - 2;

    // create array of structs containing data
    utils::stock::StockDayData* initialData = partI::loadStockData(reader);
    utils::stock::StockDayData* dataToSort = new utils::stock::StockDayData[dataSize];

    // run each algorithm multiple times
    // and get average runtime

    const int totalRuns = 1000;
    int totalTime = 0;

    // merge sort
    for (int i = 0; i < totalRuns; ++i) {
        std::copy(initialData, initialData + dataSize, dataToSort);
        totalTime += (int)utils::timer::timeit<std::function<void()>>([dataToSort, dataSize]() {algo::mergeSort(dataToSort, 0, dataSize);});
    }
    double averageMergeSortTime = ((double)totalTime) / totalRuns;

    // quick sort
    for (int i = 0; i < totalRuns; ++i) {
        std::copy(initialData, initialData + dataSize, dataToSort);
        totalTime += (int)utils::timer::timeit<std::function<void()>>([dataToSort, dataSize]() {algo::quickSort(dataToSort, 0, dataSize);});
    }

    double averageQuickSortTime = ((double)totalTime) / totalRuns;

    std::cout << "Average merge sort time: " << averageMergeSortTime << "us" << std::endl;
    std::cout << "Average quick sort time: " << averageQuickSortTime << "us" << std::endl;

    delete[] initialData;
    delete[] dataToSort;

}

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
				 (unsigned)std::stoi(currLine[5]),
				 (unsigned)std::stoi(currLine[6])};

		delete[] currLine;
	}

	return data;

}