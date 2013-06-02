#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE TestModule
#define BOOST_TEST_DYN_LINK

#include <vector>
#include <set>
#include <boost/test/unit_test.hpp>

#include "../Algorithm.h"

using namespace std;

bool vectorsContainSame(vector<int> &a, vector<int> &b) {
	if (a.size() == b.size()) {
		set<int> sB;
		for (int bValue : b) {
			sB.insert(bValue);
		}
		for (int aValue : a) {
			if (sB.find(aValue) == sB.end()) {
				return false;
			}
		}
	} else {
		return false;
	}
	return true;
}

SparseData makeSparse(int id, double *tab, int count) {
	SparseData d;
	d.id = id;
	for (int i = 0; i < count; i++) {
		if (tab[i] != 0) {
			d.data.push_back( make_pair(i, tab[i]) );
		}
	}
	return d;
}

BOOST_AUTO_TEST_CASE( BinaryTest ) {
	vector<SparseData> testVector;
	
	const int length = 20;
	const int count = 100;
	int counter = 0;
	for (int i = 0; i < count; i++) {
		SparseData item;
		item.id = i;
		for (int j = 0; j < length; j++) {
			double value = (counter*counter) % 3;
			counter++;
			if (value) {
				item.data.push_back(make_pair(j, value));
			}
		}
		testVector.push_back(item);
	}
	
	vector<int> outer_range;
	vector<int> inner_range;
	for (int i = 0; i < count; i++) {
		outer_range.push_back(i);
		inner_range.push_back(i);
	}
	
	double threshold = 0.8;
	auto groupsNaive = Algorithm::naiveBinary(testVector, outer_range, inner_range, threshold);
	auto groupsTriangle = Algorithm::triangleBinary(testVector, outer_range, inner_range, threshold, length);
	
	for (int id : inner_range) {
		BOOST_CHECK( vectorsContainSame(groupsNaive[id], groupsTriangle[id]) );
	}
}

BOOST_AUTO_TEST_CASE( RealTest ) {
	vector<SparseData> testVector;
	
	const int length = 20;
	const int count = 100;
	int counter = 0;
	for (int i = 0; i < count; i++) {
		SparseData item;
		item.id = i;
		for (int j = 0; j < length; j++) {
			double value = counter*counter % 3;
			counter++;
			if (value) {
				item.data.push_back(make_pair(j, value));
			}
		}
		testVector.push_back(item);
	}
	
	vector<int> outer_range;
	vector<int> inner_range;
	for (int i = 0; i < count; i++) {
		outer_range.push_back(i);
		inner_range.push_back(i);
	}
	
	double threshold = 0.8;
	auto groupsNaive = Algorithm::naiveReal(testVector, outer_range, inner_range, threshold);
	auto groupsTriangle = Algorithm::triangleReal(testVector, outer_range, inner_range, threshold);
	
	for (int id : inner_range) {
		BOOST_CHECK( vectorsContainSame(groupsNaive[id], groupsTriangle[id]) );
	}
}

BOOST_AUTO_TEST_CASE( TestDataTest ) {
	vector<SparseData> testVector;
	
	const int length = 10;
	const int count = 4;
	double data[count][length] = {
		{1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
		{1, 2, 0, 4, 5, 6, 0, 8, 9, 10},
		{0, 2, 3, 4, 5, 6, 7, 8, 9, 0},
		{1, 0, 0, 4, 5, 0, 0, 8, 0, 10}
	};
	
	for (int i = 0; i < count; i++) {
		testVector.push_back( makeSparse(i, data[i], length) );
	}
	
	vector<int> outer_range;
	vector<int> inner_range;
	for (int i = 0; i < count; i++) {
		outer_range.push_back(i);
		inner_range.push_back(i);
	}
	
	double threshold = 0.8;
	auto groupsNaive = Algorithm::naiveBinary(testVector, outer_range, inner_range, threshold);
	auto groupsTriangle = Algorithm::triangleBinary(testVector, outer_range, inner_range, threshold, length);
	
	for (int id : inner_range) {
		cout << endl;
		cout << "ID: " << id << endl;
		for (int i : groupsNaive[id]) cout << i << endl;
		cout << endl;
		for (int i : groupsTriangle[id]) cout << i << endl;
		
		BOOST_CHECK( vectorsContainSame(groupsNaive[id], groupsTriangle[id]) );
	}
}
