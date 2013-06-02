#include <fstream>
#include <sstream>

#include "InternetDataReader.h"

using namespace std;

InternetDataReader::InternetDataReader() : m_attributeCount(0)
{
}

vector<SparseData> InternetDataReader::read(string filename) {
	vector<SparseData> inputData;
	ifstream file(filename);

	int id = 0;
	string dataRow;
	SparseData sparseRow;
	while(true) {
		getline(file, dataRow);
		if(file.eof())
			break;
		sparseRow = readRow(dataRow);
		sparseRow.id = id;
		inputData.push_back(sparseRow);
		++id;
	}

	file.close();
	return inputData;
}

int InternetDataReader::attributeCount() const {
	return m_attributeCount;
}

SparseData InternetDataReader::readRow(string row) {
	SparseData sparseData;
	stringstream tokenizer(row);

	int index = 0;
	double value;
	while(tokenizer >> value) {
		if(value == 0.0) {
			++index;
			continue;
		}

		sparseData.data.push_back(make_pair(index, value));
		++index;
	}

	m_attributeCount = index;
	return sparseData;
}
