#ifndef DS_H
#define DS_H
#include "utils.h"
namespace ds {
    //max heap
    class StockHeap {
    public:
        StockHeap(std::size_t maxSize);
        StockHeap(utils::stock::StockDayData** array, std::size_t size, std::size_t maxSize);
        ~StockHeap();
        void insert(utils::stock::StockDayData item);
        utils::stock::StockDayData extract(int index);
        int getCurrentSize() const;
        void print() const;

    private:
        utils::stock::StockDayData *internalArray;
        const std::size_t maxSize;
        int currentSize;
        bool createdArray;
        int getParent(int index) const;
        int getRightChild(int index) const;
        int getLeftChild(int index) const;

        void heapifyUp(int index);
        void heapifyDown(int index);
    };
}

#endif //DS_H
