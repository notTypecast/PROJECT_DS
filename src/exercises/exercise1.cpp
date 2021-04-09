#include "../../include/exercises.h"


void partI::exercise1() {
	utils::csv::CSVReader readerAGN("../../data/agn.us.txt");
	utils::csv::CSVReader readerAINV("../../data/ainv.us.txt");
	utils::csv::CSVReader readerALE("../../data/ale.us.txt");

}

utils::stock::StockDayData* partI::loadStockData(const std::string &filePath) {
	utils::csv::CSVReader reader(filePath);
	struct utils::stock::StockDayData *data = new utils::stock::StockDayData[reader.getTotalRows() - 2];

	std::string* currLine;
	do {
		currLine = reader.getrow();

	} while (currLine[0].empty());

}