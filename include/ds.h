#ifndef DS_H
#define DS_H
#include "utils.h"
namespace ds {
    //max heap
    template<typename T>
    class Heap {
    public:
        Heap(std::size_t maxSize);
        Heap(T** array, std::size_t size, std::size_t maxSize);
        ~Heap();
        void insert(T item);
        T extract(int index);
        void print();

    private:
        T *internalArray;
        const std::size_t maxSize;
        int currentSize;
        bool createdArray;
        int getParent(int index);
        int getRightChild(int index);
        int getLeftChild(int index);

        void heapifyUp(int index);
        void heapifyDown(int index);
    };
}

#include "../src/ds/Heap.tpp"

#endif //DS_H
