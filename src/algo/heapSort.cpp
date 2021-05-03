#include "../../include/algo.h"

void algo::heapSort(utils::stock::StockDayData** data, std::size_t size) {
    ds::StockHeap heap(data, size, size);
    while (heap.getCurrentSize()) {
        // no need to save result, since extract will place it in the right position nonetheless
        heap.extract(0);
    }

}