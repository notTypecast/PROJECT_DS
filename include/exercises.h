#ifndef PROJECTDS_EXERCISES_H
#define PROJECTDS_EXERCISES_H
#include "utils.h"
#include "algo.h"
#include <cstring>
#include <regex>

namespace partI {
    utils::stock::StockDayData* loadStockData(utils::csv::CSVReader &reader);
	void exercise1(const std::string &fileName);
	void exercise2(const std::string &fileName);
	void exercise3();
	void exercise4();

}

namespace partII {


}

#endif //PROJECTDS_EXERCISES_H
