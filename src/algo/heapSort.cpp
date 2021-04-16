#include "../../include/algo.h"

void algo::heapSort(utils::stock::StockDayData** data, std::size_t size) {
    ds::StockHeap heap(data, size, size);
    while (heap.getCurrentSize()) {
        heap.extract(0);
    }

}