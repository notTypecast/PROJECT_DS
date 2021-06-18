#include "../../include/algo.h"

int algo::partition(utils::stock::StockDayData* data, int left, int right) {
    // using the right-most element as pivot
    int pivotIndex = (left + right) / 2;
    utils::stock::StockDayData pivot = data[pivotIndex];
    int i = left, j = right;

    // moving pivot to left-most position to facilitate final swap without multiple checks
    utils::swap<utils::stock::StockDayData>(data[pivotIndex], data[left]);
    pivotIndex = left;

    while (true) {
        while (i < right && ((data[i].open < pivot.open) || (data[i].open == pivot.open && data[i].date <= pivot.date))) {
            ++i;
        }
        while (j > left && ((data[j].open > pivot.open) || (data[j].open == pivot.open && data[j].date >= pivot.date))) {
            --j;
        }
        if (i >= j) {
            utils::swap<utils::stock::StockDayData>(data[pivotIndex], data[j]);
            return j;
        }
        utils::swap<utils::stock::StockDayData>(data[i], data[j]);
    }

}

void algo::quickSort(utils::stock::StockDayData* data, int left, int right) {
    if (left < right) {
        int partition_index = algo::partition(data, left, right);
        quickSort(data, left, partition_index - 1);
        quickSort(data, partition_index + 1, right);
    }

}
