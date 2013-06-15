#include <algorithm>
#include <cmath>
#include <limits>
#include <vector>
#include <iostream>

#include "Algorithm.h"
#include "Reporter.h"
#include "Timer.h"

using namespace std;

struct {
	bool operator() (pair<int, double> a, pair<int, double> b) { 
		return (a.second < b.second);
	}
} comp_object;

int binary_lookup(double element, vector<pair<int, double>> &tab);
double binarySimilarity(SparseData &a, SparseData &b);
double vectorDifference(SparseData &a, SparseData &b);
double vectorLength(SparseData &s);

vector<Algorithm::IDVector> Algorithm::perform(Algorithm::AlgorithmType type, std::vector<SparseData> &data, std::vector<int> &outer, std::vector<int> &inner, double sim, int attr) {
	switch(type) {
	case NAIVE_BINARY:
		return naiveBinary(data, outer, inner, sim);
	case NAIVE_REAL:
		return naiveReal(data, outer, inner, sim);
	case TRIANGLE_BINARY:
		return triangleBinary(data, outer, inner, sim, attr);
	case TRIANGLE_REAL:
		return triangleReal(data, outer, inner, sim);
	}
}

vector<Algorithm::IDVector> Algorithm::naiveBinary(vector<SparseData> &data, vector<int> &outer, vector<int> &inner, double sim) {
	vector<IDVector> result;
	double time_algo;
	
	Timer::instance().startMeasure();
	for (int innerID : inner) {
		IDVector idv;
		for (int outerID : outer) {
			if (binarySimilarity(data[innerID], data[outerID]) >= sim) {
				idv.push_back( outerID );
			}
		}
		result.push_back( idv );
	}
	time_algo = Timer::instance().finishMeasure();
	
	Reporter::instance().addReport( string("Algorithm time: ") + to_string(time_algo) + string("s") );
	
	return result;
}

vector<Algorithm::IDVector> Algorithm::naiveReal(vector<SparseData> &data, vector<int> &outer, vector<int> &inner, double sim) {
	vector<IDVector> result;
	double time_algo;
	
	Timer::instance().startMeasure();
	double vecCoefficient = (double) (sim + 1.0) / (2.0 * sim);
	double simCoefficient = (double) sqrt(-4.0*sim*sim + (sim+1.0)*(sim+1.0)) / (2.0 * sim);
	
	for (int innerID : inner) {
		IDVector idv;
		SparseData modData = data[innerID];
		double modSimilarity = vectorLength(data[innerID]) * simCoefficient;
		
		for (auto &p : modData.data) {
			p.second *= vecCoefficient;
		}
		
		for (int outerID : outer) {
			if (vectorDifference(modData, data[outerID]) <= modSimilarity) {
				idv.push_back( outerID );
			}
		}
		result.push_back( idv );
	}
	time_algo = Timer::instance().finishMeasure();
	
	Reporter::instance().addReport( string("Algorithm time: ") + to_string(time_algo) + string("s") );

	return result;
}

vector<Algorithm::IDVector> Algorithm::triangleBinary(vector<SparseData> &data, vector<int> &outer, vector<int> &inner, double sim, int attr) {
	vector<IDVector> result;
	double time_sort, time_trig;
	
	// sorting data
	Timer::instance().startMeasure();
	vector<pair<int, double>> idVector;
	for (int outerID : outer) {
		double outerDist = (double) data[outerID].data.size() / attr;
		idVector.push_back( make_pair(outerID, outerDist) );
	}
	sort(idVector.begin(), idVector.end(), comp_object);
	time_sort = Timer::instance().finishMeasure();
	
	// variables used for statistics
	int total_count = 0;
	int min_count = numeric_limits<int>::max();
	int max_count = 0;
	
	// triangle algorithm
	Timer::instance().startMeasure();
	for (int innerID : inner) {
		IDVector idv;
		idv.push_back( innerID );
		
		double innerDist = (double) data[innerID].data.size() / attr;
		auto it = idVector.begin() + binary_lookup(innerDist, idVector);
		int counter = 0;
		
		if (it != idVector.end()) {
			auto itNext = it;
			++itNext;
			while (itNext != idVector.end() && (double) itNext->second - it->second <= 1.0 - sim) {
				counter++;
				if (binarySimilarity(data[innerID], data[itNext->first]) >= sim && innerID != itNext->first) {
					idv.push_back( itNext->first );
				}
				++itNext;
			}
		}
		
		auto itPrev = it;
		while ((double) it->second - itPrev->second <= sim) {
			counter++;
			if (binarySimilarity(data[innerID], data[itPrev->first]) >= sim && innerID != itPrev->first) {
				idv.push_back( itPrev->first );
			}
			if (itPrev != idVector.begin()) {
				--itPrev;
			} else {
				break;
			}
		}
		
		// calculate stats for this similarity group
		total_count += counter;
		min_count = min<int>(counter, min_count);
		max_count = max<int>(counter, max_count);
		
		result.push_back( idv );
	}
	time_trig = Timer::instance().finishMeasure();
	
	// report results
	Reporter::instance().addReport( string("Pesimestic estimation min: ") + to_string(min_count) );
	Reporter::instance().addReport( string("Pesimestic estimation avg: ") + to_string(total_count / inner.size()) );
	Reporter::instance().addReport( string("Pesimestic estimation max: ") + to_string(max_count) );
	Reporter::instance().addReport( string("Sorting time: ") + to_string(time_sort) + string("s") );
	Reporter::instance().addReport( string("Triangle algorithm time: ") + to_string(time_trig) + string("s") );
	
	return result;
}

vector<Algorithm::IDVector> Algorithm::triangleReal(vector<SparseData> &data, vector<int> &outer, vector<int> &inner, double sim) {
	vector<IDVector> result;
	double time_sort, time_trig;
	
	// sorting data
	Timer::instance().startMeasure();
	vector<pair<int, double>> idVector;
	for (int outerID : outer) {
		idVector.push_back( make_pair(outerID, vectorLength(data[outerID])) );
	}
	
	sort(idVector.begin(), idVector.end(), comp_object);
	time_sort = Timer::instance().finishMeasure();
	
	// variables used for statistics
	int total_count = 0;
	int min_count = numeric_limits<int>::max();
	int max_count = 0;
	
	// triangle algorithm
	Timer::instance().startMeasure();
	double vecCoefficient = (double) (sim + 1.0) / (2.0 * sim);
	double simCoefficient = (double) sqrt(-4.0*sim*sim + (sim+1.0)*(sim+1.0)) / (2.0 * sim);
	
	for (int innerID : inner) {
		IDVector idv;
		idv.push_back( innerID );
		int counter = 0;
		
		SparseData modData = data[innerID];
		double vLength = vectorLength(data[innerID]);
		double modSimilarity = vLength * simCoefficient;
		double modDataLength = vLength * vecCoefficient;
		
		for (auto &p : modData.data) {
			p.second *= vecCoefficient;
		}

		auto it = idVector.begin() + binary_lookup(modDataLength, idVector);
		
		if (it != idVector.end()) {
			auto itNext = it;
			++itNext;
			while (itNext != idVector.end() && (double) itNext->second - modDataLength <= modSimilarity) {
				counter++;
				if (vectorDifference(modData, data[itNext->first]) <= modSimilarity && innerID != itNext->first) {
					idv.push_back( itNext->first );
				}
				++itNext;
			}
		}
		
		auto itPrev = it;
		while ((double) modDataLength - itPrev->second <= modSimilarity) {
			counter++;
			if (vectorDifference(modData, data[itPrev->first]) <= modSimilarity && innerID != itPrev->first) {
				idv.push_back( itPrev->first );
			}
			if (itPrev != idVector.begin()) {
				--itPrev;
			} else {
				break;
			}
		}
		
		// calculate stats for this similarity group
		total_count += counter;
		min_count = min<int>(counter, min_count);
		max_count = max<int>(counter, max_count);
		
		result.push_back( idv );
	}
	time_trig = Timer::instance().finishMeasure();
	
	// report results
	Reporter::instance().addReport( string("Pesimestic estimation min: ") + to_string(min_count) );
	Reporter::instance().addReport( string("Pesimestic estimation avg: ") + to_string(total_count / inner.size()) );
	Reporter::instance().addReport( string("Pesimestic estimation max: ") + to_string(max_count) );
	Reporter::instance().addReport( string("Sorting time: ") + to_string(time_sort) + string("s") );
	Reporter::instance().addReport( string("Triangle algorithm time: ") + to_string(time_trig) + string("s") );
	
	return result;
}

int binary_lookup(double element, vector<pair<int, double>> &tab) {
	int first = 0, last = tab.size() - 1, middle;
	while (last - first > 1) {
		middle = (last + first) / 2;
		if (tab[middle].second > element) {
			last = middle;
		} else if (tab[middle].second < element) {
			first = middle;
		} else {
			return middle;
		}
	}
	return middle;
}

double binarySimilarity(SparseData &a, SparseData &b) {
	int common = 0;
	int ptrA = 0;
	int ptrB = 0;
	
	while (ptrA < a.data.size() && ptrB < b.data.size()) {
		if (a.data[ptrA].first < b.data[ptrB].first) {
			ptrA++;
		} else if (a.data[ptrA].first > b.data[ptrB].first) {
			ptrB++;
		} else if (a.data[ptrA].second && b.data[ptrB].second) {
			common++;
			ptrA++;
			ptrB++;
		} else {
			ptrA++;
			ptrB++;
		}
	}
	
	return (double) common / (a.data.size() + b.data.size() - common);
}

double vectorDifference(SparseData &a, SparseData &b) {
	double sum = 0;
	int ptrA = 0;
	int ptrB = 0;
	
	while (ptrA < a.data.size() && ptrB < b.data.size()) {
		if (a.data[ptrA].first < b.data[ptrB].first) {
			sum += (double) a.data[ptrA].second * a.data[ptrA].second;
			ptrA++;
		} else if (a.data[ptrA].first > b.data[ptrB].first) {
			sum += (double) b.data[ptrB].second * b.data[ptrB].second;
			ptrB++;
		} else {
			double d = (double) a.data[ptrA].second - b.data[ptrB].second;
			sum += (double) d * d;
			ptrA++;
			ptrB++;
		} 
	}
	
	while (ptrA < a.data.size()) {
		sum += (double) a.data[ptrA].second * a.data[ptrA].second;
		ptrA++;
	}
	
	while (ptrB < b.data.size()) {
		sum += (double) b.data[ptrB].second * b.data[ptrB].second;
		ptrB++;
	}
	
	return (double) sqrt(sum);
}

double vectorLength(SparseData &s) {
	double sum = 0;
	for (auto &p : s.data) {
		sum += p.second * p.second;
	}
	return (double) sqrt(sum);
}
