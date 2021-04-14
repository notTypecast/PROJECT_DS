#include "../../include/exercises.h"


void partI::exercise1() {
	utils::csv::CSVReader readerAGN("../../data/agn.us.txt");
	utils::csv::CSVReader readerAINV("../../data/ainv.us.txt");
	utils::csv::CSVReader readerALE("../../data/ale.us.txt");

}

utils::stock::StockDayData* partI::loadStockData(utils::csv::CSVReader &reader) {
	struct utils::stock::StockDayData *data = new utils::stock::StockDayData[reader.getTotalRows() - 2];

	std::string* currLine;
	int index = 0;
	while (true) {

		// this will delete the previously allocated memory
		currLine = reader.getrow();
		if (currLine[0].empty()) break;
		// TODO: add data to struct
		data[index++] = {utils::date::convertStringToTimestamp(currLine[0]),
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