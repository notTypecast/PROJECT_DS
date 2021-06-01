#include "../../include/utils.h"

/* Converts date string of format: YYYY-MM-DD
 * to UNIX timestamp (total seconds since 1970-1-1)
 */
std::time_t utils::date::convertStringToTimestamp(const std::string &dateStr) {
    // separate year, month and day and turn them to integers
    int year = stoi(dateStr.substr(0, 4));
    int month = stoi(dateStr.substr(5, 2));
    int day = stoi(dateStr.substr(8));

    // get total years passed since 1970
    time_t totalYears = year - 1970;
    // convert to seconds
    time_t dateTimestamp = totalYears * utils::date::YEARTOSECONDS;

    // add extra day for each leap year since 1970
    for (int i = 1970; i < year; ++i) {
        if ((i % 400 == 0) || (i % 4 == 0 && i % 100 != 0)) {
            dateTimestamp += utils::date::DAYTOSECONDS;
        }
    }

    // calculate months in seconds
    for (int i = 1; i < month; ++i) {
        // special case for February
        if (i == 2) {
            // add 29 days (in seconds) if leap year, else 28
            if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0)) {
                dateTimestamp += 29 * utils::date::DAYTOSECONDS;
            } else {
                dateTimestamp += 28 * utils::date::DAYTOSECONDS;
            }
            continue;
        }

        // add 30 or 31 days depending on month
        // since i starts at 1, i-1 starts at 0
        // %2 is used so 0 -> month with 31 days and 1 -> month with 30 days
        // %7 is used so the result will be the opposite for August and months after it
        if (((i - 1) % 7) % 2) {
            dateTimestamp += 30 * utils::date::DAYTOSECONDS;
        } else {
            dateTimestamp += 31 * utils::date::DAYTOSECONDS;
        }
    }

    // add days of current month in seconds
    // remove 12 hours so the timestamp doesn't register as the next day
    dateTimestamp += day * utils::date::DAYTOSECONDS - utils::date::DAYTOSECONDS / 2;

    return dateTimestamp;

}

/* Converts date string of format: YYYY-MM-DD
 * to int of total days passed since 1970
 */
int utils::date::convertStringToDays(const std::string &dateStr) {
    // Convert string to UNIX timestamp (seconds since 1970)
    std::time_t seconds = utils::date::convertStringToTimestamp(dateStr);
    // return timestamp divided by DAYTOSECONDS (seconds in a day)
    return (int) (seconds / utils::date::DAYTOSECONDS);

}