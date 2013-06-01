#ifndef IREADER_H
#define IREADER_H

#include "SparseData.h"

/*
 * Abstract class used as an iterface for specific classes loading data sets.
 */
class IReader {
public:
	/*
	 * Defines type of input data interpretation
	 */
	enum ReadMode {
		REAL = 0,
		BINARY,
		INVALID_MODE
	};

	virtual ~IReader() {}

	/*
	 * @brief Reads file contents and returns a vector of sparse data.
	 * 
	 * @param filename Name of the file to be read.
	 * @return A sequence of read data.
	 */
	virtual std::vector<SparseData> read(std::string filename, ReadMode mode) = 0;
	
	/*
	 * @brief Returns the number of attributes in the data set.
	 * 
	 * @return Number of attributes.
	 */
	virtual int attributeCount() const = 0;
};

#endif
