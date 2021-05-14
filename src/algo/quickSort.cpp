#include "../../include/algo.h"

int algo::partition(utils::stock::StockDayData* data, int left, int right) {
    // using the right-most element as pivot
    int pivotIndex = (left + right) / 2;
    utils::stock::StockDayData pivot = data[pivotIndex];
    int index = left - 1;

    for (int j = left; j < right; ++j) {
        // if open values are equal, dates are checked to ensure the sorting is stable
        if (data[j].open < pivot.open || (data[j].open == pivot.open && data[j].date < pivot.date)) {
            utils::swap<utils::stock::StockDayData>(data[++index], data[j]);
        }
    }

    utils::swap<utils::stock::StockDayData>(data[++index], data[pivotIndex]);

    return index;
}

void algo::quickSort(utils::stock::StockDayData* data, int left, int right) {
    if (left < right) {
        int partition_index = algo::partition(data, left, right);
        quickSort(data, left, partition_index - 1);
        quickSort(data, partition_index + 1, right);
    }

}
