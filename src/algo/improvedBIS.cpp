#include "../../include/algo.h"

int algo::improvedBIS(utils::stock::StockDayData *data, std::size_t dataSize, int dateTimestamp) {
    if (dateTimestamp < data[0].dayTimestamp || dateTimestamp > data[dataSize - 1].dayTimestamp) {
        return -1;
    }

    int left = 0;
    int right = (int)(dataSize - 1);
    int next = std::ceil((long double)(dataSize - 1) * (dateTimestamp - data[left].dayTimestamp) / (data[right].dayTimestamp - data[left].dayTimestamp));
    int size = (int)dataSize;

    while (dateTimestamp != data[next].dayTimestamp && left < right) {
        int i = 0;
        //linear search if range contains 3 elements or less
        if (size <= 3) {
            //try to find element in range
            for (i = 0; i < size; ++i) {
                if (data[left + i].dayTimestamp == dateTimestamp) {
                    //return element volume if found
                    return data[left + i].volume;
                }
            }
            //element not found, exit
            return -1;
        }
        double sizeSqrt = std::sqrt(size);
        int currentDataIndex;
        if (dateTimestamp >= data[next].dayTimestamp) {
            while (true) {
                currentDataIndex = (int)(next + i*sizeSqrt);
                if (currentDataIndex >= dataSize) {
                    break;
                }
                if (dateTimestamp > data[currentDataIndex].dayTimestamp) {
                    // adjusting step size by multiplying by 2 every time. This ensures exponential steps.
                    i = !i ? 1 : i * 2;
                }
                else {
                    break;
                }
            }
            // located the range using exponential steps
            right = (int)(next + i*sizeSqrt);
            left = (int)(next + ((double)i/2)*sizeSqrt);
        }
        else {
            while (true) {
                currentDataIndex = (int)(next - i*sizeSqrt);
                if (currentDataIndex < 0) {
                    break;
                }
                if (dateTimestamp < data[currentDataIndex].dayTimestamp) {
                    // exponential steps
                    i = !i ? 1 : i * 2;
                }
                else {
                    break;
                }
            }
            right = (int)(next - ((double)i/2)*sizeSqrt);
            left = (int)(next - i*sizeSqrt);
        }
        // if new right and left positions exceed bounds, setting them
        // equal to last and first index respectively.
        if (right >= dataSize) {
            right = (int)(dataSize - 1);
        }
        if (left < 0) {
            left = 0;
        }

        /*
         * By now, we have an approximate position of the desired element between the
         * exponential steps. To locate the element, we perform a modified version of binary search among
         * the elements whose indices are multiples of sqrt(size).
         * If one of these elements is the element we're looking for, the search is over and the corresponding volume
         * is returned.
         * If that's not the case, this modified version will locate the subarray of size sqrt(size) and
         * adjust left and right positions accordingly. This will define the bounds of the subarray which will be
         * searched during the next iteration of the outer while loop.
         *
         * This could be done with a simple linear search, but a binary search is more efficient.
         */
        while (true) {
            int middle = (int)((right + left) / 2);

            if (dateTimestamp == data[middle].dayTimestamp) {
                return data[middle].volume;
            }

            if (middle + sizeSqrt >= right || middle - sizeSqrt <= left) {
                break;
            }

            if (dateTimestamp < data[middle].dayTimestamp) {
                right = (int)(middle - sizeSqrt);
            }
            else {
                left = (int)(middle + sizeSqrt);
            }
        }

        size = right - left + 1;
        next = (int)(left + std::floor((long double)size * (dateTimestamp - data[left].dayTimestamp) / (data[right].dayTimestamp - data[left].dayTimestamp)) - 1);
    }
    if (dateTimestamp == data[next].dayTimestamp) {
        return data[next].volume;
    }
    return -1;
}