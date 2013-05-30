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
	const int length = 10;
	const int count = 4;
	double testData[count][length] = {
		{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 
		{1, 2, 0, 4, 5, 6, 0, 8, 9, 10}, 
		{0, 2, 3, 4, 5, 6, 7, 8, 9, 0}, 
		{1, 0, 0, 4, 5, 0, 0, 8, 0, 10}
	};
	vector<SparseData> testDataVector;
	for (int i = 0; i < count; i++) {
		testDataVector.push_back( makeSparseData(i, testData[i], length) );
	}
	
	// Test ranges
	int outer[] = {0, 1, 2, 3};
	int inner[] = {0, 2};
	vector<int> outer_range(outer, outer + 4);
	vector<int> inner_range(inner, inner + 2);
	
	// Algorithm
	double similarity = 0.5;
	auto groups = Algorithm::naiveBinary( testDataVector, outer_range, inner_range, similarity );
	//auto groups = Algorithm::naiveReal( testDataVector, outer_range, inner_range, similarity );
	//auto groups = Algorithm::triangleBinary( testDataVector, outer_range, inner_range, similarity, length );
	//auto groups = Algorithm::triangleReal( testDataVector, outer_range, inner_range, similarity, length );
	
	// Print results
	for (unsigned int i = 0; i < groups.size(); i++) {
		cout << "Similar to " << inner_range[i] << ":" << endl;
		for (int id : groups[i]) {
			cout << id << endl;
		}
		cout << endl;
	}
		
	return 0;
}