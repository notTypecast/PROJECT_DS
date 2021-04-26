#include "../../include/algo.h"

utils::stock::StockDayData* algo::countingSort(utils::stock::StockDayData *data, std::size_t size) {
    //get max close value
    int maxCloseValue = -1;
    int newCloseVal;
    for (int i = 0; i < size; ++i) {
        if ((newCloseVal = (int)roundf(data[i].close)) > maxCloseValue) {
            maxCloseValue = newCloseVal;
        }
    }

    //output array is 1-based, so allocate size+1 total structs
    utils::stock::StockDayData *output = new utils::stock::StockDayData[size + 1];
    int *count = new int[maxCloseValue + 1];
    for (int i = 0; i < maxCloseValue+1; ++i) {
        count[i] = 0;
    }

    for (int i = 0; i < size; ++i) {
        ++count[(int)roundf(data[i].close)];
    }

    for (int i = 1; i < maxCloseValue + 1; ++i) {
        count[i] = count[i] + count[i - 1];
    }

    for (int i = (int) size-1; i >= 0; --i) {
        newCloseVal = (int)roundf(data[i].close);
        if (count[newCloseVal] == 0) {
            std::cout << "test: " << data[i].close << std::endl;
        }
        // this causes problems if output array size is not size+1
        output[count[newCloseVal]] = data[i];
        --count[newCloseVal];
    }

    delete[] count;
    return output;
}