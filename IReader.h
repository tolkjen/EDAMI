#ifndef IREADER_H
#define IREADER_H

#include "SparseData.h"

/*
 * Abstract class used as an iterface for specific classes loading data sets.
 */
class IReader {
public:
	/*
	 * Reads file contents and returns a vector of sparse data. Depending on 
	 * the value of binarize parameter, attribute values are turned into
	 * binary form or not.
	 * 
	 * @param filename Name of the file to be read.
	 * @param binarize If true, attribute values are binarized. If not, thay are not.
	 * @return A sequence of read data.
	 */
	virtual std::vector<SparseData> read(std::string filename, bool binarize) = 0;
	
protected:
	
};

#endif
