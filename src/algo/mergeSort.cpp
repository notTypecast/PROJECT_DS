#include "../../include/algo.h"

void algo::merge(int arr[], int left, int middle, int right) {
    //get size of subarrays
    int leftArraySize = middle - left + 1;
    int rightArraySize = right - middle;

    //temp arrays
    int *tmpLeftArr = new int[leftArraySize];
    int *tmpRightArr = new int[rightArraySize];

    int i, j;

    //copy data to temp arrays
    for (i = 0; i < leftArraySize; ++i) {
        tmpLeftArr[i] = arr[left + i];
    }
    for (j = 0; j < rightArraySize; ++j) {
        tmpRightArr[j] = arr[middle + 1 + j];
    }

    i = 0; //index of left subarray
    j = 0; //index of right subarray
    int k = left; //index of merged array


    while (i < leftArraySize && j < rightArraySize) {
        if (tmpLeftArr[i] <= tmpRightArr[j]) {
            arr[k] = tmpLeftArr[i++];
        }
        else {
            arr[k] = tmpRightArr[j++];
        }
        ++k;
    }

    while (i < leftArraySize) {
        arr[k++] = tmpLeftArr[i++];
    }

    while (j < rightArraySize) {
        arr[k++] = tmpRightArr[j++];
    }

    delete[] tmpLeftArr;
    delete[] tmpRightArr;


}

void algo::mergeSort(int arr[], int left, int right) {
    //end if left index is >= right index
    if (left >= right) {
        return;
    }

    //get middle index
    int middle = (right + left) / 2;

    //call mergeSort on left and right subarrays recursively
    algo::mergeSort(arr, left, middle);
    algo::mergeSort(arr, middle + 1, right);
    //merge resulting arrays
    algo::merge(arr, left, middle, right);

}

