#ifndef ALGO_H
#define ALGO_H

#include <cmath>
#include "utils.h"
#include "ds.h"

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

    /// \brief Implementation of the heapsort algorithm.
    /// \param data Double pointer to array of StockDayData structs; function changes pointer to array, so double pointer is required.
    /// \param size Size of array.
    void heapSort(utils::stock::StockDayData** data, std::size_t size);

    /// \brief Implementation of the counting sort algorithm.
    /// \param data Pointer to array of StockDayData structs.
    /// \param size Size of array.
    /// \returns 1-based sorted array of (size+1).
    utils::stock::StockDayData* countingSort(utils::stock::StockDayData* data, std::size_t size);

    /// \brief Implementation of the binary search algorithm.
    /// \param data Pointer to array of StockDayData structs.
    /// \param left Left index in array.
    /// \param right Right index in array.
    /// \param date Date to search for.
    /// \returns total volume corresponding to given date, -1 if not found.
    int binarySearch(utils::stock::StockDayData* data, int left, int right, const std::string &date);

    /// \brief Implementation of the interpolation search algorithm.
    /// \param data Pointer to array of StockDayData structs.
    /// \param left Left index in array.
    /// \param right Right index in array.
    /// \param date Date to search for.
    /// \returns total volume corresponding to given date, -1 if not found.
    int interpolationSearch(utils::stock::StockDayData* data, int left, int right, const std::string &date);

    /// \brief Implementation of the BIS algorithm.
    /// \param data Pointer to array of StockDayData structs.
    /// \param dataSize Size of array.
    /// \param date Date to search for.
    /// \returns total volume corresponding to given date, -1 if not found.
    int binaryInterpolationSearch(utils::stock::StockDayData* data, std::size_t dataSize, const std::string &date);

    /// \brief Implementation of the BIS algorithm, with improved worst case complexity.
    /// \param data Pointer to array of StockDayData structs.
    /// \param dataSize Size of array.
    /// \param date Date to search for.
    /// \returns total volume corresponding to given date, -1 if not found.
    int improvedBIS(utils::stock::StockDayData* data, std::size_t dataSize, const std::string &date);




}

#endif //ALGO_H
