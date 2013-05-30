#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE TestModule
#define BOOST_TEST_DYN_LINK

#include <vector>
#include <iostream>
#include <boost/test/unit_test.hpp>

#include "../Algorithm.h"

using namespace std;

BOOST_AUTO_TEST_CASE( BinaryTest ) {
	vector<SparseData> testVector;
	
	const int length = 20;
	const int count = 20;
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
	
	double threshold = 0.75;
	auto groupsNaive = Algorithm::naiveBinary(testVector, outer_range, inner_range, threshold);
	auto groupsTriangle = Algorithm::triangleBinary(testVector, outer_range, inner_range, threshold, length);
	
	for (int id : inner_range) {
		BOOST_CHECK_EQUAL(groupsNaive[id].size(), groupsTriangle[id].size());
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
	
	double threshold = 0.75;
	auto groupsNaive = Algorithm::naiveReal(testVector, outer_range, inner_range, threshold);
	auto groupsTriangle = Algorithm::triangleReal(testVector, outer_range, inner_range, threshold);
	
	for (int id : inner_range) {
		BOOST_CHECK_EQUAL(groupsNaive[id].size(), groupsTriangle[id].size());
	}
}
