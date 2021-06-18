#include "../../include/algo.h"

int algo::partition(utils::stock::StockDayData* data, int left, int right) {
    // using the right-most element as pivot
    int pivotIndex = (left + right) / 2;
    utils::stock::StockDayData pivot = data[pivotIndex];
    int i = left, j = right;

    while (true) {
        while (i < right && data[i].open <= pivot.open) {
            ++i;
        }
        while (j > left && data[j].open >= pivot.open) {
            --j;
        }
        if (i >= j) {
            break;
        }
        utils::swap<utils::stock::StockDayData>(data[i], data[j]);
    }

    // Checking positions to swap appropriately, since mid is used as pivot
    if (pivotIndex > i) {
        utils::swap<utils::stock::StockDayData>(data[pivotIndex], data[i]);
        return i;
    }
    else {
        utils::swap<utils::stock::StockDayData>(data[pivotIndex], data[j]);
        return j;
    }
}

void algo::quickSort(utils::stock::StockDayData* data, int left, int right) {
    if (left < right) {
        int partition_index = algo::partition(data, left, right);
        quickSort(data, left, partition_index - 1);
        quickSort(data, partition_index + 1, right);
    }

}
