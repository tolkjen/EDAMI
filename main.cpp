#include <iostream>
#include "SparseData.h"

using namespace std;

int main() {
	SparseData d;
	/*shared_ptr<IReader> reader( new KryszkiewiczReader );
	vector<SparseData> data = reader->read("plik.dat", false);
	
	shared_ptr<IAlgorithm> algo( new TriangleAlgorithm() );
	algo->setDistanceMeasure( shared_ptr(new RealDistance(threshold)) );
	algo->setDataSet( data );
	
	vector<vector<int>> results = algo->calculate(outer_range, inner_range );
	print results;
	
	for t in algo->timings:
		print t.description
		print t.value*/
		
	return 0;
}