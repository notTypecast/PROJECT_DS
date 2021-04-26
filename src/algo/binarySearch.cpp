#include "../../include/algo.h"

int algo::binarySearch(utils::stock::StockDayData *data, int left, int right, const std::string &date) {
    if (right >= left) {
        int middle = (right + left) / 2;

        if (data[middle].date == date) {
            return data[middle].volume;
        }

        if (data[middle].date > date) {
            return algo::binarySearch(data, left, middle - 1, date);
        }

        return algo::binarySearch(data, middle + 1, right, date);
    }

    return -1;
}