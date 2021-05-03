#include "../../include/utils.h"

// Print all values of a stock struct
void utils::stock::printStockStruct(StockDayData data) {
    std::cout << data.date << " " << data.open << " " << data.high << " " << data.low << " " << data.close << " " << data.volume << " " << data.openInt;
}