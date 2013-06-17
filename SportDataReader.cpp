#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>

#include "SportDataReader.h"

using namespace std;

bool cmpPairs(pair<int, double> a, pair<int, double> b ) {
	return a.first > b.first;
}

SportDataReader::SportDataReader() : m_attributeCount(0)
{
}

vector<SparseData> SportDataReader::read(string filename) {
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

	DataDescription::iterator it;
	cout << "==================================================================================" << endl;
	cout << "Data characteristics" << endl;
	for(it = m_dataCharacteristics.begin(); it != m_dataCharacteristics.end(); ++it) {
		it->second->avgVal = (double) it->second->presentInRows / (double) inputData.size();

		cout << "Id: [" << it->first << "], present in rows: [" << it->second->presentInRows << "], min occurences: [" << it->second->minVal
			 << "], max occurences: [" << it->second->maxVal << "], average occurences: [" << it->second->avgVal << "]" << endl;
	}
	cout << "==================================================================================" << endl;

	file.close();
	return inputData;
}

int SportDataReader::attributeCount() const {
	return m_attributeCount;
}

SparseData SportDataReader::readRow(string row) {
	SparseData sparseData;
	stringstream tokenizer(row);

	int index;
	double value;
	while(tokenizer >> index >> value) {
		sparseData.data.push_back(make_pair(index, value));
		m_attributeCount = (index > m_attributeCount) ? index : m_attributeCount;

		if(m_dataCharacteristics.find(index) == m_dataCharacteristics.end()) {
			m_dataCharacteristics[index] = shared_ptr<DataCharacteristics>(new DataCharacteristics);
			m_dataCharacteristics[index]->maxVal = value;
			m_dataCharacteristics[index]->minVal = value;
			m_dataCharacteristics[index]->presentInRows = 1;
		}
		else {
			m_dataCharacteristics[index]->maxVal = (m_dataCharacteristics[index]->maxVal > value) ? m_dataCharacteristics[index]->maxVal : value;
			m_dataCharacteristics[index]->minVal = (m_dataCharacteristics[index]->minVal < value) ? m_dataCharacteristics[index]->minVal : value;
		}
		m_dataCharacteristics[index]->presentInRows++;
	}

	sort(sparseData.data.begin(), sparseData.data.end(), cmpPairs);
	return sparseData;
}
