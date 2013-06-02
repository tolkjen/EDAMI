#ifndef INTERNETDATAREADER_H
#define INTERNETDATAREADER_H

#include "IReader.h"

/*
 * Class loading data set from repository at: http://archive.ics.uci.edu/ml/datasets/Internet+Usage+Data
 */
class InternetDataReader: public IReader {
public:
	InternetDataReader();
	virtual ~InternetDataReader() {}

	/*
	 * @see std::vector<SparseData> IReader::read(std::string filename)
	 */
	virtual std::vector<SparseData> read(std::string filename);

	/*
	 * @see int IReader::attributeCount() const
	 */
	virtual int attributeCount() const;

private:
	/*
	 * @brief Reads one row of input data.
	 *
	 * @param row Data row.
	 * @return Sparse data.
	 */
	SparseData readRow(std::string row);

	/*
	 * Number of attributes in one row o input data.
	 */
	int m_attributeCount;
};

#endif
