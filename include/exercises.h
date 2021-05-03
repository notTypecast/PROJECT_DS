#ifndef PROJECTDS_EXERCISES_H
#define PROJECTDS_EXERCISES_H

#include "utils.h"
#include "algo.h"
#include <cstring>
#include <regex>

/*
 * This namespace contains assignments and helper functions regarding
 * the first part of the project.
 */
namespace partI {
    /// \brief Loads data from files.
    /// \param reader CSVReader object corresponding to a single data file
    /// \details This function is used to load the data from each file to
    /// an array of StockDayData structs. These arrays are then used to complete
    /// the assignments
    utils::stock::StockDayData *loadStockData(utils::csv::CSVReader &reader);

    /*
     * Each function below corresponds to an exercise.
     */
    void exercise1(const std::string &fileName);

    void exercise2(const std::string &fileName);

    void exercise3();

    void exercise4();

}

namespace partII {


}

#endif //PROJECTDS_EXERCISES_H
