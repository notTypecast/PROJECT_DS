#include "../../include/algo.h"

int algo::binaryInterpolationSearch(utils::stock::StockDayData *data, std::size_t dataSize, int dateTimestamp) {
    if (dateTimestamp < data[0].dayTimestamp || dateTimestamp > data[dataSize - 1].dayTimestamp) {
        return -1;
    }
    int left = 0;
    int right = (int) (dataSize - 1);

    // Dynamic range of UNIX timestamps in the data is dangerously large.
    // This could cause problems when performing floating point operations.
    // To avoid this, instead of unix timestamps, dates were converted to total days elapsed since 1970-01-01.

    // long double conversion is used to increase floating point precision
    // without it, if dateTimestamp and data[left].date are very close but not equal, the division will result in 0 because of not enough precision to store result
    // and next = ceil(0) = 0, whereas it should be next = 1 unless dateTimestamp == data[left].date
    int next = (int) (std::ceil((long double) (dataSize - 1) * (dateTimestamp - data[left].dayTimestamp) / (data[right].dayTimestamp - data[left].dayTimestamp)));
    int size = (int) dataSize;

    while (dateTimestamp != data[next].dayTimestamp) {
        int i = 0;
        // performing linear search if size is less than 4.
        if (size <= 3) {
            for (i = 0; i < size; ++i) {
                if (data[left + i].dayTimestamp == dateTimestamp) {
                    return data[left + i].volume;
                }
            }
            return -1;
        }
        double sizeSqrt = std::sqrt(size);
        int currentDataIndex;
        if (dateTimestamp >= data[next].dayTimestamp) {
            while (true) {
                currentDataIndex = (int) (next + i * sizeSqrt);

                // checking if the jump exceeded the array bounds
                if (currentDataIndex >= dataSize) {
                    break;
                }
                if (dateTimestamp > data[currentDataIndex].dayTimestamp) {
                    ++i;
                } else {
                    break;
                }
            }
            right = (int) (next + i * sizeSqrt);
            left = (int) (next + (i - 1) * sizeSqrt);
        } else {
            while (true) {
                currentDataIndex = (int) (next - i * sizeSqrt);

                // checking bounds again
                if (currentDataIndex < 0) {
                    break;
                }
                if (dateTimestamp < data[currentDataIndex].dayTimestamp) {
                    ++i;
                } else {
                    break;
                }
            }
            right = (int) (next - (i - 1) * sizeSqrt);
            left = (int) (next - i * sizeSqrt);
        }
        // if new right and left positions exceed bounds, setting them
        // equal to last and first index respectively.
        if (right >= dataSize) {
            right = (int) (dataSize - 1);
        }
        if (left < 0) {
            left = 0;
        }
        // calculating new size and next prediction
        size = right - left + 1;
        next = (int) (left + std::floor((long double) (size - 1) * (dateTimestamp - data[left].dayTimestamp) / (data[right].dayTimestamp - data[left].dayTimestamp)));
    }
    if (dateTimestamp == data[next].dayTimestamp) {
        return data[next].volume;
    }
    return -1;
}