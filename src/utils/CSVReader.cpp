#include "../../include/utils.h"

// Constructor
utils::csv::CSVReader::CSVReader(const std::string &filePath) {
    // open file
    fileReaderStream.open(filePath, std::ifstream::in);
    if (!fileReaderStream.good()) throw std::exception();

    // pass through every row of file to determine total rows
    TOTALROWS = 0;
    std::string temp;
    while (fileReaderStream.good()) {
        getline(fileReaderStream, temp);
        ++TOTALROWS;
    }
    // reset reader stream
    fileReaderStream.clear();
    fileReaderStream.seekg(0);

    // file is CSV, therefore determine total columns by counting the commas in the first line and adding 1
    // this also serves to skip the first line (which isn't data, but the column names)
    // so when .getrow() is first called, the actual first row of data is returned
    std::string firstLine;
    getline(fileReaderStream, firstLine);
    TOTALCOLUMNS = std::count(firstLine.begin(), firstLine.end(), ',') + 1;

}

// Destructor
utils::csv::CSVReader::~CSVReader() {
    if (fileReaderStream.is_open()) fileReaderStream.close();
}

// Get next row in file
std::string *utils::csv::CSVReader::getrow() {
    // return nullptr if end of file has been reached
    if (!fileReaderStream.good()) {
        return nullptr;
    }
    // get next row and parse it using .parserow()
    // then return resulting string array
    std::string row;
    std::getline(fileReaderStream, row);
    return parserow(row);
}

// Getter for TOTALCOLUMNS
std::size_t utils::csv::CSVReader::getTotalColumns() const {
    return TOTALCOLUMNS;
}

// Getter for TOTALROWS
std::size_t utils::csv::CSVReader::getTotalRows() const {
    return TOTALROWS;
}

// Parses a row (line) of the file into desired format
std::string *utils::csv::CSVReader::parserow(const std::string &rowStr) const {
    // stringstream serves to build string until end character is met (comma)
    std::stringstream holder;
    // allocate memory for string array that will be returned
    std::string *rowArray = new std::string[TOTALCOLUMNS];
    // loop through row characters
    int index = 0;
    for (const char &ch : rowStr) {
        // when comma is met, current string contained in holder is complete
        if (ch == ',') {
            // save string to array
            rowArray[index++] = holder.str();
            // empty holder and move on to next iteration
            holder.str("");
            continue;
        }
        // add character to holder
        holder << ch;
    }
    // remaining data must be placed at the end of the array
    // since there is no comma after the last column
    rowArray[index] = holder.str();
    return rowArray;
}