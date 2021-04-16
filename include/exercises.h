#ifndef PROJECTDS_EXERCISES_H
#define PROJECTDS_EXERCISES_H
#include "utils.h"
#include "algo.h"
#include <cstring>

namespace partI {
    utils::stock::StockDayData* loadStockData(utils::csv::CSVReader &reader);
	void exercise1(const std::string &fileName);
	void exercise2(const std::string &fileName);

}

namespace partII {


}

#endif //PROJECTDS_EXERCISES_H
