#ifndef IDISTANCE_H
#define IDISTANCE_H

#include "SparseData.h"

/*
 * Abstract class used as an interface for specific classes calculating
 * distance between two sparse vectors. 
 */
class IDistance {
public:
	/*
	 * Returns a value of distance between two sparse vectors given as
	 * parameters.
	 * 
	 * @param a First sparse vector.
	 * @param b Second sparse vector.
	 * @return Value of distance between vectors.
	 */
	virtual double value(SparseData &a, SparseData &b) = 0;
};

#endif
