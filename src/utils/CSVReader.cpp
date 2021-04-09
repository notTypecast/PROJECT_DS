#include "../../include/utils.h"

utils::csv::CSVReader::CSVReader(const std::string &filePath) {
	fileReaderStream.open(filePath, std::ifstream::in);
	if (!fileReaderStream.good()) throw std::exception();

	std::string firstLine;
	getline(fileReaderStream, firstLine);
	TOTALCOLUMNS = std::count(firstLine.begin(), firstLine.end(), ',') + 1;

}

utils::csv::CSVReader::~CSVReader() {
	if (fileReaderStream.is_open()) fileReaderStream.close();
}

std::string* utils::csv::CSVReader::getrow() {
	if (!fileReaderStream.good()) {
		return nullptr;
	}
	std::string row;
	std::getline(fileReaderStream, row);
	return parserow(row);
}

std::size_t utils::csv::CSVReader::getTotalColumns() {
	return TOTALCOLUMNS;
}

std::string* utils::csv::CSVReader::parserow(const std::string &rowStr) {
	std::stringstream holder;
	std::string* rowArray = new std::string[TOTALCOLUMNS];
	int index = 0;
	for (const char &ch : rowStr) {
		if (ch == ',') {
			rowArray[index++] = holder.str();
			holder.str(""); // emptying the stream
			continue;
		}
		holder << ch;
	}
	rowArray[index] = holder.str();
	return rowArray;
}