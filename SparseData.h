#ifndef SPARSEDATA_H
#define SPARSEDATA_H

#include <algorithm>
#include <vector>

/*
 * Data structure holding information about sparse attribute representation 
 * and row identifier.
 */
struct SparseData {
	/*
	 * Holds pairs of attribute column number and attribute value.
	 */
	std::vector<std::pair<int, double>> data;
	
	/*
	 * Row identifier.
	 */
	int id;
};

#endif
