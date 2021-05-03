#include "../../include/ds.h"

// All comparisons on stock heap are performed between the close values of each struct
// this is because HeapSort sorts by close value

// Constructor 1
ds::StockHeap::StockHeap(std::size_t maxSize) : createdArray(true), internalArray(new utils::stock::StockDayData[maxSize]), currentSize(0), maxSize(maxSize) {
};

// Constructor 2
ds::StockHeap::StockHeap(utils::stock::StockDayData** array, std::size_t size, std::size_t maxSize) : createdArray(false), internalArray(new utils::stock::StockDayData[maxSize]), currentSize(0), maxSize(maxSize) {
    // size of heap cannot be smaller than size of passed array
    if (maxSize < size) {
        throw std::invalid_argument("maxSize cannot be smaller than size.");
    }

    // add each element of internal array to self
    // since insert method is used, internal array will always be heap
    for (int i = 0; i < size; ++i) {
        insert((*array)[i]);
    }

    // change array passed to be equal to the internal array
    // thus, changes on the heap will affect array passed
    // this is also why double pointer is required
    delete[] *array;
    *array = internalArray;
};

// Destructor
ds::StockHeap::~StockHeap() {
    if (createdArray) {
        delete[] internalArray;
    }
}

// Returns index of parent of element at passed index
int ds::StockHeap::getParent(int index) const {
    return (index - 1) / 2;
}

// Returns index of right child of element at passed index
int ds::StockHeap::getRightChild(int index) const {
    return 2*index + 2;
}

// Returns index of left child of element at passed index
int ds::StockHeap::getLeftChild(int index) const {
    return 2*index + 1;
}

// Heapify up method
void ds::StockHeap::heapifyUp(int index) {
    // Exit if element is at index 0 (root of heap)
    if (!index) {
        return;
    }
    int parentIndex = getParent(index);
    // if value of this element is larger than value of parent, swap them and heapify up again (for new index of this element, which is parent index)
    if (internalArray[index].close > internalArray[parentIndex].close) {
        utils::swap<utils::stock::StockDayData>(internalArray[index], internalArray[parentIndex]);
        heapifyUp(parentIndex);
    }
}

// Heapify down method
void ds::StockHeap::heapifyDown(int index) {
    int leftChildIndex = getLeftChild(index);
    int rightChildIndex = getRightChild(index);

    // if there is no right child
    if (rightChildIndex >= currentSize) {
        // if there is a left child and its value is larger than this element's, swap them
        // no further heapify down is necessary, because since there was no right child, the left child had no children
        if (leftChildIndex < currentSize && internalArray[index].close < internalArray[leftChildIndex].close) {
            utils::swap(internalArray[index], internalArray[leftChildIndex]);
        }
        return;
    }

    // if children's values are smaller than this element's, stop
    if (internalArray[index].close >= internalArray[leftChildIndex].close && internalArray[index].close >= internalArray[rightChildIndex].close) {
        return;
    }

    // swap this element with the child with the largest value
    int indexOfMax = internalArray[leftChildIndex].close > internalArray[rightChildIndex].close ? leftChildIndex : rightChildIndex;
    utils::swap(internalArray[index], internalArray[indexOfMax]);

    // call heapifyDown for this element again
    heapifyDown(indexOfMax);
}

// insert given element to heap
void ds::StockHeap::insert(utils::stock::StockDayData &item) {
    // throw exception if heap is full
    if (currentSize == maxSize) {
        throw std::out_of_range("Heap max size reached.");
    }

    // add item to internal array
    internalArray[currentSize] = item;
    // call heapify up on the item and increase array size after
    heapifyUp(currentSize++);
}

// extract element at given index from heap
utils::stock::StockDayData ds::StockHeap::extract(int index) {
    // throw exception if given index is out of range
    if (index >= currentSize) {
        throw std::out_of_range("Index out of range.");
    }

    // swap element at given index with final element and decrement array size
    utils::swap(internalArray[index], internalArray[--currentSize]);
    // call heapify down on final element (which is now at given index)
    heapifyDown(index);
    // return extracted element
    return internalArray[currentSize];
}

// Getter for current heap size
int ds::StockHeap::getCurrentSize() const {
    return currentSize;
}

// Print the heap (in array form)
void ds::StockHeap::print() const {
    for (int i = 0; i < currentSize; ++i) {
        std::cout << internalArray[i].close << " ";
    }
}