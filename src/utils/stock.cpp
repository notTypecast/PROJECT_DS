#include <utility>

#include "../../include/utils.h"

// Print all values of a stock struct
void utils::stock::printStockStruct(const StockDayData &data) {
    std::cout << data.date << " " << data.open << " " << data.high << " " << data.low << " " << data.close << " " << data.volume << " " << data.openInt;
}

int utils::stock::SDV_KeyDate::operator%(int divisor) const {
    // get sum of ASCII codes of all characters in date string
    int sum = 0;
    for (char i: date) {
        sum += (int) i;
    }
    // return the sum % the number passed after the mod operator
    return sum % divisor;
}