#include "../../include/algo.h"

int algo::interpolationSearch(utils::stock::StockDayData *data, int left, int right, const std::string &date) {
    int position;

    if (left == right) {
        if (data[left].date == date) {
            return data[left].volume;
        }
        return -1;
    }

    if (left < right && date >= data[left].date && date <= data[right].date) {
        int valueTimestamp = utils::date::convertStringToDays(date);
        int leftTimestamp = utils::date::convertStringToDays(data[left].date);
        int rightTimestamp = utils::date::convertStringToDays(data[right].date);

        position = (int)(left + ((double)(right - left)/(rightTimestamp - leftTimestamp))*(valueTimestamp - leftTimestamp));

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