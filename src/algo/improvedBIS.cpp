#include "../../include/algo.h"
#define STD utils::date::convertStringToDays

int algo::improvedBIS(utils::stock::StockDayData *data, std::size_t dataSize, const std::string &date) {
    if (date < data[0].date || date > data[dataSize - 1].date) {
        return -1;
    }

    int dateTimestamp = STD(date);
    int left = 0;
    int right = (int)(dataSize - 1);
    int next = std::ceil((long double)(dataSize - 1) * (dateTimestamp - STD(data[left].date)) / (STD(data[right].date) - STD(data[left].date)));
    int size = (int)dataSize;

    while (date != data[next].date && left < right) {
        int i = 0;
        double sizeSqrt = std::sqrt(size);
        int currentDataIndex;
        if (date >= data[next].date) {
            while (true) {
                currentDataIndex = (int)(next + i*sizeSqrt);
                if (currentDataIndex >= dataSize) {
                    break;
                }
                if (date > data[currentDataIndex].date) {
                    // adjusting step size by multiplying by 2 every time. This ensures exponential steps.
                    i = !i ? 1 : i *= 2;
                }
                else {
                    break;
                }
            }
            // located the range using exponential steps
            right = (int)(next + i*sizeSqrt);
            left = (int)(next + (i/2)*sizeSqrt);
        }
        else {
            while (true) {
                currentDataIndex = (int)(next - i*sizeSqrt);
                if (currentDataIndex < 0) {
                    break;
                }
                if (date < data[currentDataIndex].date) {
                    // exponential steps
                    i = !i ? 1 : i *= 2;
                }
                else {
                    break;
                }
            }
            right = (int)(next - (i/2)*sizeSqrt);
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

            if (date == data[middle].date) {
                return data[middle].volume;
            }

            if (middle + sizeSqrt >= right || middle - sizeSqrt <= left) {
                break;
            }

            if (date < data[middle].date) {
                right = (int)(middle - sizeSqrt);
            }
            else {
                left = (int)(middle + sizeSqrt);
            }
        }

        size = right - left + 1;
        next = (int)(left + std::floor((long double)size * (dateTimestamp - STD(data[left].date)) / (STD(data[right].date) - STD(data[left].date))) - 1);
    }
    if (date == data[next].date) {
        return data[next].volume;
    }
    return -1;
}