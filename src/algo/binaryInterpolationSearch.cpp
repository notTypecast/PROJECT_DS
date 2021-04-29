#include "../../include/algo.h"
#define STD utils::date::convertStringToDays

int algo::binaryInterpolationSearch(utils::stock::StockDayData *data, std::size_t dataSize, const std::string &date) {
    if (date < data[0].date || date > data[dataSize - 1].date) {
        return -1;
    }
    int left = 0;
    int right = (int)(dataSize - 1);
    //Instead of unix timestamps, dates were converted to total days elapsed since 1970-01-01
    std::time_t dateTimestamp = STD(date);
    //long double conversion is used to increase floating point precision
    //without it, if dateTimestamp and data[left].date are very close but not equal, the division will result in 0 because of not enough precision to store result
    //and next = ceil(0) = 0, whereas it should be next = 1 unless dateTimestamp == data[left].date
    int next = std::ceil((long double)dataSize * (dateTimestamp - STD(data[left].date)) / (STD(data[right].date) - STD(data[left].date)));
    int size = (int)dataSize;

    while (date != data[next].date && left < right) {
        int i = 0;
        if (size <= 3) {
            for (; i < size; ++i) {
                if (data[left + i].date == date) {
                    return data[left + i].volume;
                }
            }
            return -1;
        }
        double sizeSqrt = std::sqrt(size);
        if (date >= data[next].date) {
            int currentDataIndex;
            while (true) {
                currentDataIndex = (int)(next + i*sizeSqrt);
                if (currentDataIndex >= dataSize) {
                    break;
                }
                if (date > data[currentDataIndex].date) {
                    ++i;
                }
                else {
                    break;
                }
            }
            right = (int)(next + i*sizeSqrt);
            left = (int)(next + (i - 1)*sizeSqrt);
        }
        else {
            int currentDataIndex;
            while (true) {
                currentDataIndex = (int)(next - i*sizeSqrt);
                if (currentDataIndex < 0) {
                    break;
                }
                if (date < data[currentDataIndex].date) {
                    ++i;
                }
                else {
                    break;
                }
            }
            right = (int)(next - (i - 1)*sizeSqrt);
            left = (int)(next - i*sizeSqrt);
        }
        if (right >= dataSize) {
            right = (int)(dataSize - 1);
        }
        if (left < 0) {
            left = 0;
        }
        size = right - left + 1;
        next = (int)(left + std::floor((long double)size * (dateTimestamp - STD(data[left].date)) / (STD(data[right].date) - STD(data[left].date))) - 1);
    }
    if (date == data[next].date) {
        return data[next].volume;
    }
    return -1;
}