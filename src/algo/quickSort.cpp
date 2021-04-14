#include "../../include/algo.h"

int algo::partition(utils::stock::StockDayData* data, int left, int right) {
    utils::stock::StockDayData pivot = data[right];
    int index = left - 1;

    for (int j = left; j < right; ++j) {
        if (data[j].open < pivot.open || (data[j].open == pivot.open && data[j].date < pivot.date)) {
            utils::swap<utils::stock::StockDayData>(data[++index], data[j]);
        }
    }

    utils::swap<utils::stock::StockDayData>(data[++index], data[right]);

    return index;
}

void algo::quickSort(utils::stock::StockDayData* data, int left, int right) {
    if (left < right) {
        int partition_index = algo::partition(data, left, right);
        quickSort(data, left, partition_index - 1);
        quickSort(data, partition_index + 1, right);
    }

}
