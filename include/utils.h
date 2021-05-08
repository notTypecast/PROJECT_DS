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

    // Simple swap helper function.
    template<typename T>
    void swap(T &item1, T &item2);

    namespace string {
        void lower(std::string& in);
    }

    // Helper functions to deal with arrays.
    namespace array {
        template<typename T>
        bool compare(const T arr1[], std::size_t arr1Size, const T arr2[], std::size_t arr2Size);

        template<typename T>
        T *duplicate(const T arr[], std::size_t arrSize);
    }

    namespace stock {
        // This struct is used to hold stock data for a single day.
        struct StockDayData {
            std::string date;
            float open;
            float high;
            float low;
            float close;
            int volume;
            unsigned int openInt;
        };

        // Basic struct holding date string and volume int
        struct StockDayVolume {
            std::string date;
            int volume;
            virtual bool operator< (const StockDayVolume& other) const = 0;
            virtual bool operator<= (const StockDayVolume& other) const = 0;
            virtual bool operator> (const StockDayVolume& other) const = 0;
            virtual bool operator>= (const StockDayVolume& other) const = 0;
            virtual bool operator== (const StockDayVolume& other) const = 0;
            virtual bool operator!= (const StockDayVolume& other) const = 0;
        };

        // StockDayVolume struct using DATE as key for comparisons
        struct SDV_KeyDate : StockDayVolume {
            inline bool operator< (const StockDayVolume& other) const {return date < other.date;}
            inline bool operator<= (const StockDayVolume& other) const {return date <= other.date;};
            inline bool operator> (const StockDayVolume& other) const {return date > other.date;}
            inline bool operator>= (const StockDayVolume& other) const {return date >= other.date;}
            inline bool operator== (const StockDayVolume& other) const {return date == other.date;}
            inline bool operator!= (const StockDayVolume& other) const {return date != other.date;}
            inline friend std::ostream & operator<< (std::ostream &out, const struct SDV_KeyDate& s) {
                out << s.date << " " << s.volume;
                return out;
            }
        };

        // StockDayVolume struct using VOLUME as key for comparisons
        struct SDV_KeyVolume : StockDayVolume {
            inline bool operator< (const StockDayVolume& other) const {return volume < other.volume;}
            inline bool operator<= (const StockDayVolume& other) const {return volume <= other.volume;};
            inline bool operator> (const StockDayVolume& other) const {return volume > other.volume;}
            inline bool operator>= (const StockDayVolume& other) const {return volume >= other.volume;}
            inline bool operator== (const StockDayVolume& other) const {return volume == other.volume;}
            inline bool operator!= (const StockDayVolume& other) const {return volume != other.volume;}
            inline friend std::ostream & operator<< (std::ostream &out, const struct SDV_KeyVolume& s) {
                out << s.date << " " << s.volume;
                return out;
            }
        };

        void printStockStruct(const StockDayData &data);

    }


    namespace date {
        const int YEARTOSECONDS = 31536000; // not taking leap years into account
        const int DAYTOSECONDS = 86400;

        /// \brief Converts given string to UNIX timestamp.
        std::time_t convertStringToTimestamp(const std::string &dateStr);

        /// \brief Converts UNIX timestamp to number of days.
        int convertStringToDays(const std::string &dateStr);
    }


    namespace csv {
        /// \brief Wrapper class to handle csv parsing.
        class CSVReader {
        public:
            CSVReader(const std::string &filePath);

            ~CSVReader();

            /// \returns Single row as array of strings, each element corresponds to a row value
            /// \details Size of returned array will be TOTALCOLUMNS, since each element of the array
            /// is a csv value.
            std::string *getrow();

            std::size_t getTotalColumns() const;

            /// \returns Total number of rows in CSV file. Includes column row and empty lines.
            std::size_t getTotalRows() const;

        private:
            std::size_t TOTALCOLUMNS;
            std::size_t TOTALROWS;
            std::ifstream fileReaderStream;

            /// \brief Splits row on commas.
            /// \returns Array of strings
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
        // pattern to match the YYYY-MM-DD format.
        const std::string DATE = "^\\d{4}\\-(0?[1-9]|1[012])\\-(0?[1-9]|[12][0-9]|3[01])$";
    }

}

// including tpp files, since non-specialized template implementations
// need to be in the same file as their declarations.
// using .tpp extension to distinguish source files containing template implementations.
#include "../src/utils/array.tpp"
#include "../src/utils/utils.tpp"
#include "../src/utils/timer.tpp"


#endif
