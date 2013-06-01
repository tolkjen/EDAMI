#include <fstream>

#include "InternetDataReader.h"

using namespace std;

InternetDataReader::InternetDataReader() : m_attributeCount(0)
{
}

vector<SparseData> InternetDataReader::read(string filename, ReadMode mode) {
	vector<SparseData> inputData;
	ifstream file(filename);

	string dataRow;
	SparseData sparseRow;
	while(file.eof() == false) {
		getline(file, dataRow);

		switch(mode) {
		case REAL:
			sparseRow = readRealRow(dataRow);
			break;
		case BINARY:
			sparseRow = readBinaryRow(dataRow);
			break;
		}

		inputData.push_back(sparseRow);
	}

	/*
	 * We can read size of only last row, beacause all rows have the same length.
	 * If sparseRow is empty then size will be 0 anyway.
	 */
	m_attributeCount = sparseRow.data.size();
	file.close();
	return inputData;
}

int InternetDataReader::attributeCount() const {
	return m_attributeCount;
}

SparseData InternetDataReader::readRealRow(string row) {
	// TODO: implement
}

SparseData InternetDataReader::readBinaryRow(string row) {
	// TODO: implement
}
