#include "../../include/algo.h"

int algo::interpolationSearch(utils::stock::StockDayData *data, int left, int right, const std::string &date) {
    int position;

    if (left <= right && date >= data[left].date && date <= data[right].date) {
        std::time_t valueTimestamp = utils::date::convertStringToTimestamp(date);
        std::time_t leftTimestamp = utils::date::convertStringToTimestamp(data[left].date);
        std::time_t rightTimestamp = utils::date::convertStringToTimestamp(data[right].date);

        position = (int)(left + ((double)(right - left) / (double)(rightTimestamp - leftTimestamp))*(double)(valueTimestamp - leftTimestamp));

        if (data[position].date == date) {
            return data[position].volume;
        }

        if (data[position].date < date) {
            return algo::interpolationSearch(data, position + 1, right, date);
        }

        if (data[position].date > date) {
            return algo::interpolationSearch(data, left, position - 1, date);
        }
    }
    return -1;
}