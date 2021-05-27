#include "../../include/algo.h"

int algo::interpolationSearch(utils::stock::StockDayData *data, int left, int right, int dateTimestamp) {
    int position;

    if (left == right) {
        if (data[left].dayTimestamp == dateTimestamp) {
            return data[left].volume;
        }
        return -1;
    }

    if (left < right && dateTimestamp >= data[left].dayTimestamp && dateTimestamp <= data[right].dayTimestamp) {
        position = (int)(left + ((double)(right - left)/(data[right].dayTimestamp - data[left].dayTimestamp))*(dateTimestamp - data[left].dayTimestamp));

        if (data[position].dayTimestamp == dateTimestamp) {
            return data[position].volume;
        }

        if (data[position].dayTimestamp < dateTimestamp) {
            return algo::interpolationSearch(data, position + 1, right, dateTimestamp);
        }

        if (data[position].dayTimestamp > dateTimestamp) {
            return algo::interpolationSearch(data, left, position - 1, dateTimestamp);
        }
    }
    return -1;
}