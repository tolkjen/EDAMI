#ifndef RANGEPARSER_H
#define RANGEPARSER_H

#include <vector>
#include <string>

class RangeParser {
public:
	static std::vector<int> parseRowRanges(std::string rawRanges);

private:
	static std::vector<int> rangeToRows(std::string range);
};

#endif
