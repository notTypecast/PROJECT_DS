#include "../../include/algo.h"

int algo::partition(int arr[], int left, int right) {
    int pivot = arr[right];
    int index = left - 1;

    for (int j = left; j < right; ++j) {
        if (arr[j] < pivot) {
            utils::swap(arr[++index], arr[j]);
        }
    }

    utils::swap(arr[++index], arr[right]);

    return index;
}

void algo::quickSort(int arr[], int left, int right) {
    if (left < right) {
        int partition_index = algo::partition(arr, left, right);
        quickSort(arr, left, partition_index - 1);
        quickSort(arr, partition_index + 1, right);
    }

}
