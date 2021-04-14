#ifndef ALGO_H
#define ALGO_H

#include "utils.h"

namespace algo {
    //mergeSort
    void merge(utils::stock::StockDayData* data, int left, int middle, int right);
    void mergeSort(utils::stock::StockDayData* data, int left, int right);
    //quickSort
    int partition(int arr[], int left, int right);
    void quickSort(int arr[], int left, int right);
}

#endif //ALGO_H
