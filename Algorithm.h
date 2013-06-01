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
	
	/*
	 * Defines type of algorithm
	 */
	enum AlgorithmType {
		NAIVE_BINARY = 0,
		NAIVE_REAL,
		TRIANGLE_BINARY,
		TRIANGLE_REAL,
		INVALID_TYPE
	};

public:
	/*
	 * @brief Generic method for all defined algorithms. Performs method based on type argument.
	 *
	 * @param type Defines which algorithm should be performed.
	 * @param outer Contains IDs of vectors from which similar groups are built.
	 * @param inner Contains IDs of vectors for which groups are built.
	 * @param sim Similarity threshold.
	 * @param attr Total number of attributes in the data set (triangleBinary algorithm only).
	 * @return A vector of IDVectors. Each IDVector corresponds to one group and holds info about similar vector IDs.
	 */
	static std::vector<IDVector> perform(AlgorithmType type, std::vector<SparseData> &data, std::vector<int> &outer, std::vector<int> &inner, double sim, int attr = 0);

	/*
	 * @brief Finds groups of similar vectors in naive way treating them as binary
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
	 * @brief Finds groups of similar vectors in naive way treating them as real
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
	 * @brief Finds groups of similar vectors using triangle inequation and treating
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
	 * @brief Finds groups of similar vectors using triangle inequation and treating
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
