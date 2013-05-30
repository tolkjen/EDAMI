#ifndef DISTANCE_H
#define DISTANCE_H

#include "SparseData.h"

class Similarity {
public:
	static double binary(SparseData &a, SparseData &b);
	static double real(SparseData &a, SparseData &b);
};

#endif
