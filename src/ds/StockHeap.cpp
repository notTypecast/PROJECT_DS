#include "../../include/ds.h"


ds::StockHeap::StockHeap(std::size_t maxSize) : createdArray(true), internalArray(new utils::stock::StockDayData[maxSize]), currentSize(0), maxSize(maxSize) {
};


ds::StockHeap::StockHeap(utils::stock::StockDayData** array, std::size_t size, std::size_t maxSize) : createdArray(false), internalArray(new utils::stock::StockDayData[maxSize]), currentSize(0), maxSize(maxSize) {
    if (maxSize < size) {
        throw std::invalid_argument("maxSize cannot be smaller than size.");
    }

    for (int i = 0; i < size; ++i) {
        insert((*array)[i]);
    }

    delete[] *array;
    *array = internalArray;
};


ds::StockHeap::~StockHeap() {
    if (createdArray) {
        delete[] internalArray;
    }
}


int ds::StockHeap::getParent(int index) const {
    return (index - 1) / 2;
}


int ds::StockHeap::getRightChild(int index) const {
    return 2*index + 2;
}


int ds::StockHeap::getLeftChild(int index) const {
    return 2*index + 1;
}



void ds::StockHeap::heapifyUp(int index) {
    if (!index) {
        return;
    }
    int parentIndex = getParent(index);
    if (internalArray[index].close > internalArray[parentIndex].close) {
        utils::swap<utils::stock::StockDayData>(internalArray[index], internalArray[parentIndex]);
        heapifyUp(parentIndex);
    }
}

void ds::StockHeap::heapifyDown(int index) {
    int leftChildIndex = getLeftChild(index);
    int rightChildIndex = getRightChild(index);

    if (rightChildIndex >= currentSize) {
        return;
    }

    if (internalArray[index].close >= internalArray[leftChildIndex].close && internalArray[index].close >= internalArray[rightChildIndex].close) {
        return;
    }

    int indexOfMax = internalArray[leftChildIndex].close > internalArray[rightChildIndex].close ? leftChildIndex : rightChildIndex;
    utils::swap(internalArray[index], internalArray[indexOfMax]);

    heapifyDown(indexOfMax);
}

void ds::StockHeap::insert(utils::stock::StockDayData item) {
    if (currentSize == maxSize) {
        throw std::out_of_range("Heap max size reached.");
    }

    internalArray[currentSize] = item;
    heapifyUp(currentSize++);
}

utils::stock::StockDayData ds::StockHeap::extract(int index) {
    if (!currentSize) {
        throw std::out_of_range("Heap is empty.");
    }

    utils::swap(internalArray[index], internalArray[currentSize - 1]);
    heapifyDown(index);
    return internalArray[--currentSize];
}

int ds::StockHeap::getCurrentSize() const {
    return currentSize;
}

void ds::StockHeap::print() const {
    for (int i = 0; i < currentSize; ++i) {
        std::cout << internalArray[i].close << " ";
    }
}