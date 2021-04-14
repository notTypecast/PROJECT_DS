#ifndef ALGO_H
#define ALGO_H

#include "utils.h"

namespace algo {
    /// \brief Merges two sorted subarrays in place.
    /// \param data Pointer to array of StockDayData structs.
    /// \param left Left index.
    /// \param right Right index.
    void merge(utils::stock::StockDayData* data, int left, int middle, int right);
    /// \brief Implementation of the merge sort algorithm.
    /// \param data Pointer to array of StockDayData structs.
    /// \param left Left index.
    /// \param right Right index.
    void mergeSort(utils::stock::StockDayData* data, int left, int right);

    /// \brief Partitions the data array.
    /// \param data Pointer to array of StockDayData structs.
    /// \param left Left index.
    /// \param right Right index.
    /// \returns Index of pivot after partitioning.
    int partition(utils::stock::StockDayData* data, int left, int right);
    /// \brief Implementation of the quicksort algorithm.
    /// \param data Pointer to array of StockDayData structs.
    /// \param left Left index.
    /// \param right Right index.
    void quickSort(utils::stock::StockDayData* data, int left, int right);
}

#endif //ALGO_H
