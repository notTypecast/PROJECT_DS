#include "../../include/utils.h"

int utils::stock::SDV_KeyDate::operator%(int divisor) const {
    // get sum of ASCII codes of all characters in date string
    int sum = 0;
    for (char i: date) {
        sum += (int) i;
    }
    // return the sum % the number passed after the mod operator
    return sum % divisor;
}