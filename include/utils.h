#ifndef UTILS_H
#define UTILS_H

#include <cstdio>
#include <string>
#include <ctime>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <chrono>
#include <fstream>
#include <functional>
#include <algorithm>

namespace utils {

    template<typename T>
    void swap(T &item1, T &item2);

    namespace array {
        template<typename T>
        bool compare(const T arr1[], std::size_t arr1Size, const T arr2[], std::size_t arr2Size);

        template<typename T>
        T *duplicate(const T arr[], std::size_t arrSize);
    }

    namespace stock {
        struct StockDayData {
            std::string date;
            float open;
            float high;
            float low;
            float close;
            int volume;
            unsigned int openInt;
        };

        void printStockStruct(StockDayData data);

    }


    namespace date {
        const int YEARTOSECONDS = 31536000; // not taking leap years into account
        const int DAYTOSECONDS = 86400;

        std::time_t convertStringToTimestamp(const std::string &dateStr);

        std::string convertTimestampToString(std::time_t dateTimestamp);
    }


    namespace csv {
        class CSVReader {
        public:
            CSVReader(const std::string &filePath);

            ~CSVReader();

            std::string *getrow();

            std::size_t getTotalColumns() const;

            std::size_t getTotalRows() const;

        private:
            std::size_t TOTALCOLUMNS;
            std::size_t TOTALROWS;
            std::ifstream fileReaderStream;

            std::string *parserow(const std::string &rowStr) const;
        };
    }

    namespace timer {
        /// \brief Times execution of a function.
        /// \param funcToTime Function to time.
        /// \returns Time in microseconds.
        template<typename F>
        std::time_t timeit(F funcToTime);
    }

    namespace regex {
        const std::string DATE = "^\\d{4}\\-(0?[1-9]|1[012])\\-(0?[1-9]|[12][0-9]|3[01])$";
    }

}

#include "../src/utils/array.tpp"
#include "../src/utils/utils.tpp"
#include "../src/utils/timer.tpp"


#endif
