#ifndef DS_H
#define DS_H

#include "utils.h"

/// \brief This namespace will hold all the data structures needed in the project.
namespace ds {

    /// \brief Specialized implementation of a max heap to handle StockDayData.
    class StockHeap {
    public:
        StockHeap(std::size_t maxSize);

        /// \brief Initialized the heap using an existing StockDayData array.
        /// \param array StockDayData array used to initialized the heap. Passing double pointer since we need
        /// to reassign the array to the new internal array created.
        /// \param size Size of the array passed as an argument.
        /// \param maxSize Defines max size of internal array and, as a result, the max size of the heap.
        StockHeap(utils::stock::StockDayData **array, std::size_t size, std::size_t maxSize);

        ~StockHeap();

        /// \brief Inserts StockDayData object to the heap.
        void insert(utils::stock::StockDayData &item);

        /// \brief Extracts item at given index from the heap.
        /// \details Performs necessary rearrangements to preserve max heap structure.
        utils::stock::StockDayData extract(int index);

        /// \brief Returns current size of the heap.
        int getCurrentSize() const;

        void print() const;

    private:
        utils::stock::StockDayData *internalArray;
        const std::size_t maxSize;
        int currentSize;
        bool createdArray;

        // Helper methods to get indices of nodes relative to given index.
        static int getParent(int index);

        static int getRightChild(int index);

        static int getLeftChild(int index);

        // Methods used to preserve the heap structure.
        void heapifyUp(int index);

        void heapifyDown(int index);
    };
}

#endif //DS_H
