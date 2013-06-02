#ifndef RANGEPARSER_H
#define RANGEPARSER_H

#include <vector>
#include <string>

class RangeParser {
public:
	/*
	 * @brief Parses user preferences about row ranges and converts them into vector of row numbers.
	 *
	 * @param rawRanges String with user preferences.
	 * @return Vector with row numbers.
	 */
	static std::vector<int> parseRowRanges(std::string rawRanges);

	/*
	 * @brief Converts range string (ex. "1-5") into vector of valus within that range (ex. [1, 2, 3, 4, 5]).
	 *
	 * @param range String defining range.
	 * @return Vector of values within defined range.
	 */
	static std::vector<int> rangeToRows(std::string range);
};

#endif
