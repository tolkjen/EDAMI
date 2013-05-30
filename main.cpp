#include <iostream>
#include "Algorithm.h"

using namespace std;

SparseData makeSparseData(int id, double *tab, int length) {
	SparseData result;
	result.id = id;
	for (int i = 0; i < length; i++) {
		if (tab[i] != 0) {
			result.data.push_back(make_pair(i, tab[i]));
		}
	}
	return result;
}

int main() {
	// Some test data
	double testData[][4] = {
		{1, 2, 3, 4}, 
		{1, 2, 0, 4}
	};
	vector<SparseData> testDataVector;
	for (int i = 0; i < 2; i++) {
		testDataVector.push_back( makeSparseData(i, testData[i], 4) );
	}
	
	// Test ranges
	int outer[] = {0, 1};
	int inner[] = {0};
	vector<int> outer_range(outer, outer + sizeof(outer));
	vector<int> inner_range(inner, inner + sizeof(inner));
	
	// Algorithm
	shared_ptr<Algorithm> algo(new Algorithm());
	//algo->setDistanceMeasure(shared_ptr(new));
	algo->setDataSet( testDataVector );
	auto groups = algo->calculate( outer_range, inner_range );
		
	return 0;
}