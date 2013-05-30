#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <memory>
#include "IDistance.h"

/*
 * Parent class for specific algorithms.
 */
class Algorithm {
public:
	typedef std::vector<int> IDVector;
	
public:
	/*
	 * Finds groups of similar vectors. For every vector of ID in inner, 
	 * similar vectors are found between vectors of ID in outer.
	 * 
	 * @param outer Contains IDs of vectors from which similar groups are built.
	 * @param inner Contains IDs of vectors for which groups are built.
	 * @return A vector of IDVectors. Each IDVector corresponds to one group and holds info about similar vector IDs.
	 */
	std::vector<IDVector> calculate(std::vector<int> &outer, std::vector<int> &inner) {}
	
	/*
	 * Sets a data to work on.
	 * 
	 * @param data Data to work on.
	 */
	void setDataSet(std::vector<SparseData> &data);
	
	/*
	 * Sets a pointer to an object calculating distance between two vectors.
	 * 
	 * @param dPtr Reference to an object derived from IDistance class.
	 */
	void setDistanceMeasure(std::shared_ptr<IDistance> dPtr);
	
protected:
	std::shared_ptr<IDistance> distancePtr;
	std::vector<SparseData> dataVector;
};

#endif
