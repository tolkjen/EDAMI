#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <vector>
#include "SparseData.h"

/*
 * Class holds static methods used for finding similar vectors.
 */
class Algorithm {
public:
	typedef std::vector<int> IDVector;
	
public:
	/*
	 * Finds groups of similar vectors in naive way treating them as binary 
	 * vectors. For every vector of ID in inner, similar vectors are found 
	 * between vectors of ID in outer.
	 * 
	 * @param outer Contains IDs of vectors from which similar groups are built.
	 * @param inner Contains IDs of vectors for which groups are built.
	 * @param sim Similarity threshold.
	 * @return A vector of IDVectors. Each IDVector corresponds to one group and holds info about similar vector IDs.
	 */
	static std::vector<IDVector> naiveBinary(std::vector<SparseData> &data, std::vector<int> &outer, std::vector<int> &inner, double sim);
	
	/*
	 * Finds groups of similar vectors in naive way treating them as real 
	 * vectors. For every vector of ID in inner, similar vectors are found 
	 * between vectors of ID in outer.
	 * 
	 * @param outer Contains IDs of vectors from which similar groups are built.
	 * @param inner Contains IDs of vectors for which groups are built.
	 * @param sim Similarity threshold.
	 * @return A vector of IDVectors. Each IDVector corresponds to one group and holds info about similar vector IDs.
	 */
	static std::vector<IDVector> naiveReal(std::vector<SparseData> &data, std::vector<int> &outer, std::vector<int> &inner, double sim);
	
	/*
	 * Finds groups of similar vectors using triangle inequation and treating 
	 * them as binary vectors. For every vector of ID in inner, similar 
	 * vectors are found between vectors of ID in outer.
	 * 
	 * @param outer Contains IDs of vectors from which similar groups are built.
	 * @param inner Contains IDs of vectors for which groups are built.
	 * @param sim Similarity threshold.
	 * @param attr Total number of attributes in the data set.
	 * @return A vector of IDVectors. Each IDVector corresponds to one group and holds info about similar vector IDs.
	 */	
	static std::vector<IDVector> triangleBinary(std::vector<SparseData> &data, std::vector<int> &outer, std::vector<int> &inner, double sim, int attr);
	
	/*
	 * Finds groups of similar vectors using triangle inequation and treating 
	 * them as real-valued vectors. For every vector of ID in inner, similar 
	 * vectors are found between vectors of ID in outer.
	 * 
	 * @param outer Contains IDs of vectors from which similar groups are built.
	 * @param inner Contains IDs of vectors for which groups are built.
	 * @param sim Similarity threshold.
	 * @return A vector of IDVectors. Each IDVector corresponds to one group and holds info about similar vector IDs.
	 */	
	static std::vector<IDVector> triangleReal(std::vector<SparseData> &data, std::vector<int> &outer, std::vector<int> &inner, double sim);
};

#endif
