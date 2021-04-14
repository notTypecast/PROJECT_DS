#include <iostream>
#include "../include/utils.h"
#include "../include/exercises.h"

int main() {
	utils::csv::CSVReader reader("../data/agn.us.txt");
    utils::stock::StockDayData* data = partI::loadStockData(reader);
	for (int i = 0; i < 10; ++i) {
		std::cout << data[i].timestamp << std::endl;
		std::cout << utils::date::convertTimestampToString(data[i].timestamp) << std::endl;
	}

    return 0;
}
