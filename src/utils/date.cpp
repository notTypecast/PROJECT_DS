#include "../../include/utils.h"

std::time_t utils::date::convertStringToTimestamp(const std::string &dateStr) {

	// Date format: YYYY-MM-DD
	int firstDash = dateStr.find('-');
	int secondDash = dateStr.find('-', firstDash + 1);

	int year = stoi(dateStr.substr(0, firstDash));
	int month = stoi(dateStr.substr(firstDash + 1, secondDash - firstDash - 1));
	int day = stoi(dateStr.substr(secondDash + 1));


	int totalYears = year - 1970;
	time_t dateTimestamp = totalYears * utils::date::YEARTOSECONDS;

	for (int i = 1970; i < year; ++i) {
		if ((i % 400 == 0) || (i % 4 == 0 && i % 100 != 0)) {
			dateTimestamp += utils::date::DAYTOSECONDS;
		}
	}

	// calculating months in seconds
	for (int i = 1; i < month; ++i) {
		// special case for February
		if (i == 2) {
			// checking if current year is leap year
			if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0)) {
				dateTimestamp += 29 * utils::date::DAYTOSECONDS;
			} else {
				dateTimestamp += 28 * utils::date::DAYTOSECONDS;
			}
			continue;
		}

		if (((month - 1) % 7) % 2) {
			dateTimestamp += 30 * utils::date::DAYTOSECONDS;
		} else {
			dateTimestamp += 31 * utils::date::DAYTOSECONDS;
		}
	}

	// adding current day to timestamp
	dateTimestamp += day * utils::date::DAYTOSECONDS - utils::date::DAYTOSECONDS/2;

	return dateTimestamp;

}

std::string utils::date::convertTimestampToString(std::time_t dateTimestamp) {

	struct tm * aTime = std::localtime(&dateTimestamp);


	std::stringstream ss;
	ss << std::to_string(aTime->tm_year + 1900) << '-';
	ss << (aTime->tm_mon < 9 ? "0": "") << std::to_string(aTime->tm_mon + 1) << '-';
	ss << (aTime->tm_mday < 10 ? "0" : "") << std::to_string(aTime -> tm_mday);

	return ss.str();

}