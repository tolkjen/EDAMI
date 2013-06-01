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
	virtual std::vector<SparseData> read(std::string filename, ReadMode mode);

	/*
	 * @see int IReader::attributeCount() const
	 */
	virtual int attributeCount() const;

private:
	/*
	 * @brief Reads one row of input data in normal form.
	 *
	 * @param row Data row.
	 * @return Sparse data.
	 */
	SparseData readRealRow(std::string row);

	/*
	 * @brief Reads one row of input data in binary form.
	 *
	 * @param row Data row.
	 * @return Sparse data.
	 */
	SparseData readBinaryRow(std::string row);

	/*
	 * Number of attributes in one row o input data.
	 */
	int m_attributeCount;
};

#endif
