#ifndef UTILS_H
#define UTILS_H

#include <cstdio>
#include <string>
#include <ctime>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <fstream>
#include <algorithm>

namespace utils {

    template <typename T>
    void swap(T &item1, T &item2);

    namespace array {
        template <typename T>
        bool compare(const T arr1[], std::size_t arr1Size, const T arr2[], std::size_t arr2Size);

        template <typename T>
        T* duplicate(const T arr[], std::size_t arrSize);
    }

    namespace stock {
        struct StockDayData {
            std::time_t timestamp;
            float open;
            float high;
            float low;
            float close;
            unsigned int volume;
            int openInt;
        };

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

			std::size_t getTotalColumns();


		private:
			std::size_t TOTALCOLUMNS;
			std::ifstream fileReaderStream;
			std::string *parserow(const std::string &rowStr);
		};
    }

}

#include "../src/utils/array.tpp"
#include "../src/utils/utils.tpp"

#endif
