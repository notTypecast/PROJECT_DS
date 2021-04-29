#include "../../include/algo.h"
#define STT utils::date::convertStringToTimestamp


int algo::binaryInterpolationSearch(utils::stock::StockDayData *data, std::size_t dataSize, const std::string &date) {
    if (date < data[0].date || date > data[dataSize - 1].date) {
        return -1;
    }
    int left = 0;
    int right = (int)(dataSize - 1);
    std::time_t dateTimestamp = STT(date);
    int next = std::ceil(dataSize * (dateTimestamp - STT(data[left].date)) / (STT(data[right].date) - STT(data[left].date)));
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
                currentDataIndex = (int)(next + i*sizeSqrt - 1);
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
            if (right >= dataSize) {
                right = (int)(dataSize - 1);
            }
        }
        else {
            for (; date < data[(int)(next - i*sizeSqrt + 1)].date; ++i) {std::cout << next - i*sizeSqrt + 1 << std::endl;}
            right = (int)(next - (i - 1)*sizeSqrt);
            left = (int)(next - i*sizeSqrt);
        }
        size = right - left + 1;
        next = (int)(left + std::floor(size * (dateTimestamp - STT(data[left].date)) / (STT(data[right].date) - STT(data[left].date))) - 1);
    }
    return data[next].volume;
}