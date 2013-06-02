#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <cctype>
#include <boost/algorithm/string.hpp>

using namespace std;

#include "RangeParser.h"

vector<int> RangeParser::parseRowRanges(string rawRanges) {
	vector<int> rows;

	// Remove any spaces from input data
	rawRanges.erase(remove_if(rawRanges.begin(), rawRanges.end(), isblank), rawRanges.end());

	// Split into ranges
	vector<string> ranges;
	boost::split(ranges, rawRanges, boost::is_any_of(","));

	// Split into numbers of rows
	for(string s: ranges) {
		boost::trim(s);

		if(s.find("-") == string::npos) {
			rows.push_back(atoi(s.c_str()));
		}
		else {
			vector<int> rowsFromRange = rangeToRows(s);
			rows.insert(rows.end(), rowsFromRange.begin(), rowsFromRange.end());
		}
	}

	// Sort rows and remove duplicates it there are any
	sort(rows.begin(), rows.end());
	rows.erase(unique(rows.begin(), rows.end()), rows.end());

	return rows;
}

vector<int> RangeParser::rangeToRows(string range) {
	vector<int> rangeRows;

	vector<string> boundaries;
	boost::split(boundaries, range, boost::is_any_of("-"));
	if(boundaries.size() != 2) {
		return rangeRows;
	}

	for(int i = atoi(boundaries[0].c_str()); i <= atoi(boundaries[1].c_str()); ++i) {
		rangeRows.push_back(i);
	}

	return rangeRows;
}
