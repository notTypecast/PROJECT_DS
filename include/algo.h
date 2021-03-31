#ifndef ALGO_H
#define ALGO_H

#include "utils.h"

namespace algo {
    //mergeSort
    void merge(int arr[], int left, int middle, int right);
    void mergeSort(int arr[], int left, int right);
    //quickSort
    int partition(int arr[], int left, int right);
    void quickSort(int arr[], int left, int right);
}

#endif //ALGO_H
