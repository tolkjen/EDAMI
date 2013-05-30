#include "Algorithm.h"

using namespace std;

void Algorithm::setDataSet(std::vector<SparseData> &data) {
	dataVector = data;
}

void Algorithm::setDistanceMeasure(std::shared_ptr<IDistance> dPtr) {
	distancePtr = dPtr;
}
