template <typename T>
ds::AVLTree<T> partII::loadStockDataToAVLTree(utils::csv::CSVReader &reader) {
    static_assert(std::is_base_of<utils::stock::StockDayVolume, T>::value, "T must derive from utils::stock::StockDayVolume");
    ds::AVLTree<T> tree;

    std::string *currLine;
    while (true) {
        // read new line from file
        currLine = reader.getrow();
        // stop if empty line is found
        if (currLine[0].empty()) break;
        // save data to struct in array
        T newEntry;
        newEntry.date = currLine[0];
        newEntry.volume = std::stoi(currLine[5]);
        tree.insert(newEntry);
        // delete string array allocated for line
        delete[] currLine;
    }

    return tree;
}