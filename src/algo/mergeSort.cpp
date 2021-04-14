#include "../../include/algo.h"

void algo::merge(utils::stock::StockDayData* data, int left, int middle, int right) {
    //get size of subarrays
    int leftArraySize = middle - left + 1;
    int rightArraySize = right - middle;

    //temp arrays
    utils::stock::StockDayData *tmpLeftArr = new utils::stock::StockDayData[leftArraySize];
    utils::stock::StockDayData *tmpRightArr = new utils::stock::StockDayData[rightArraySize];
    int i, j;

    //copy data to temp arrays
    for (i = 0; i < leftArraySize; ++i) {
        tmpLeftArr[i] = data[left + i];
    }
    for (j = 0; j < rightArraySize; ++j) {
        tmpRightArr[j] = data[middle + 1 + j];
    }

    i = 0; //index of left subarray
    j = 0; //index of right subarray
    int k = left; //index of merged array

    while (i < leftArraySize && j < rightArraySize) {
        /* sorting by open value
         * if open values are equal, then date will be used to sort
         * String comparison works because each individual character will be compared
         * until a non-equal character is found
         * Dates have the same format YYYY-MM-DD
         * UTF-8 (and ASCII) character codes for numbers are in order, i.e '0'<'1'<...
         */
        if (tmpLeftArr[i].open < tmpRightArr[j].open || (tmpLeftArr[i].open == tmpRightArr[j].open && tmpLeftArr[i].date < tmpRightArr[j].date)) {
            data[k] = tmpLeftArr[i++];
        }
        else {
            data[k] = tmpRightArr[j++];
        }
        ++k;
    }

    while (i < leftArraySize) {
        data[k++] = tmpLeftArr[i++];
    }

    while (j < rightArraySize) {
        data[k++] = tmpRightArr[j++];
    }

    delete[] tmpLeftArr;
    delete[] tmpRightArr;
}

void algo::mergeSort(utils::stock::StockDayData* data, int left, int right) {
    //end if left index is >= right index
    if (left >= right) {
        return;
    }

    //get middle index
    int middle = (right + left) / 2;

    //call mergeSort on left and right subarrays recursively
    algo::mergeSort(data, left, middle);
    algo::mergeSort(data, middle + 1, right);
    //merge resulting arrays
    algo::merge(data, left, middle, right);

}

