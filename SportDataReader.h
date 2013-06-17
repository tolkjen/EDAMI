#ifndef SPORTDATAREADER_H
#define SPORTDATAREADER_H

#include "IReader.h"
#include <map>
#include <memory>

struct DataCharacteristics {
	int presentInRows;
	int minVal;
	int maxVal;
	double avgVal;
};

typedef std::map<int, std::shared_ptr<DataCharacteristics> > DataDescription;

/*
 * Class loading data set from repository at:  http://glaros.dtc.umn.edu/gkhome/cluto/cluto/download
 */
class SportDataReader: public IReader {
public:
	SportDataReader();
	virtual ~SportDataReader() {}

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

	/*
	 * Data characteristics
	 */
	DataDescription m_dataCharacteristics;
};

#endif
