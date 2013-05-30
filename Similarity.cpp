#include "Similarity.h"

double Similarity::binary(SparseData &a, SparseData &b) {
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
		}
	}
	
	return (double) common / (a.data.size() + b.data.size() - common);
}

double Similarity::real(SparseData &a, SparseData &b) {
	return 0;
}
