#include "../../include/algo.h"

utils::stock::StockDayData *algo::countingSort(utils::stock::StockDayData *data, std::size_t size) {
    // get max close value
    int maxCloseValue = -1;
    int newCloseVal;
    // calculating max value in the data array
    for (int i = 0; i < size; ++i) {
        if ((newCloseVal = (int) roundf(data[i].close)) > maxCloseValue) {
            maxCloseValue = newCloseVal;
        }
    }

    // output array is 1-based, so allocate size+1 total structs
    utils::stock::StockDayData *output = new utils::stock::StockDayData[size + 1];
    // initialize count array with zeros
    int *count = new int[maxCloseValue + 1];
    for (int i = 0; i < maxCloseValue + 1; ++i) {
        count[i] = 0;
    }

    // increment count[element] by 1 for each element
    for (int i = 0; i < size; ++i) {
        ++count[(int) roundf(data[i].close)];
    }

    // set each value in count to be its previous value + the sum of all count values before it
    for (int i = 1; i < maxCloseValue + 1; ++i) {
        count[i] = count[i] + count[i - 1];
    }


    for (int i = (int) size - 1; i >= 0; --i) {
        // get integer value by rounding close float value
        newCloseVal = (int) roundf(data[i].close);
        // set current element to its position in the output array
        output[count[newCloseVal]] = data[i];
        // decrement count of current element, so next element with same value is placed before it
        // this also ensures the sorting is stable
        --count[newCloseVal];
    }

    // deallocate memory used for count array
    delete[] count;
    return output;
}