#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <boost/program_options.hpp>
#include "Algorithm.h"
#include "Timer.h"

using namespace std;

/*
 * Holds CLI arguments provided by user.
 */
struct CLIArguments {
	string inputFile;
	string targetSet;
	string searchSet;
	string algorithm;
	string interpretation;
	double treshold;
};

/*
 * @brief Parses arguments provided by user. Checks for errors and not provided arguments that are mandatory.
 *
 * @param vm Boost variable map that holds information about provided arguments.
 * @param args Values for CLI arguments provided by user.
 * @param algorithm Algorithm type that should be used in execution.
 * @return Error code
 */
int parseCLIArguments(boost::program_options::variables_map &vm, CLIArguments &args, Algorithm::AlgorithmType &algorithm);

/*
 * @brief Checks algorithm type basing on user preferences.
 *
 * @param algorithm Algorithm name that should be used in execution.
 * @param interpretation Method of data interpretation.
 * @return Algorithm type.
 */
Algorithm::AlgorithmType getAlgorithmType(string algorithm, string interpretation);

/*
 * OBSOLETE: to be removed
 */
SparseData makeSparseData(int id, double *tab, int length);

int main(int argc, char *argv[]) {
	CLIArguments args;
	Algorithm::AlgorithmType algorithm;

	// Collect CLI arguments
	boost::program_options::options_description options("Options");
	options.add_options()
		("help,h", "print help message")
		("input-data,d", boost::program_options::value<string>(&args.inputFile), "file with input data (-d flag can be omitted)")
		("target-set,r", boost::program_options::value<string>(&args.targetSet)->default_value("1"), "number of rows defining set for which similar vectors will be searched")
		("search-set,s", boost::program_options::value<string>(&args.searchSet)->default_value("all"), "number of rows defining set where similar vectors will be searched")
		("algorithm,a", boost::program_options::value<string>(&args.algorithm)->default_value("triangle"), "search algorithm")
		("interpretation,i", boost::program_options::value<string>(&args.interpretation)->default_value("real"), "data interpretation method")
		("treshold,t", boost::program_options::value<double>(&args.treshold), "Tanimoto similarity threshold value")
	;

	boost::program_options::positional_options_description defaultOption;
	defaultOption.add("input-data", 1);

	boost::program_options::variables_map vm;
	try {
		boost::program_options::store(boost::program_options::command_line_parser(argc, argv).options(options).positional(defaultOption).run(), vm);
		boost::program_options::notify(vm);
	}
	catch(...) {
		cout << "Invalid program options!" << endl;
		cout << options << endl;
		return 1;
	}

	// Help
	if(vm.count("help")) {
		cout << options << endl;
		return 0;
	}

	// Parse CLI arguments
	int ret = parseCLIArguments(vm, args, algorithm);
	if(ret != 0) {
		return ret;
	}

	// Prepare input data
	// TODO: implement

	// Some test data
	const int length = 10;
	const int count = 4;
	double testData[count][length] = {
		{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 
		{1, 2, 0, 4, 5, 6, 0, 8, 9, 10}, 
		{0, 2, 3, 4, 5, 6, 7, 8, 9, 0}, 
		{1, 0, 0, 4, 5, 0, 0, 8, 0, 10}
	};
	vector<SparseData> testDataVector;
	for (int i = 0; i < count; i++) {
		testDataVector.push_back( makeSparseData(i, testData[i], length) );
	}
	
	// Test ranges
	int outer[] = {0, 1, 2, 3};
	int inner[] = {0, 2};
	vector<int> outer_range(outer, outer + 4);
	vector<int> inner_range(inner, inner + 2);
	
	// Algorithm
	Timer::instance().startMeasure();
	auto groups = Algorithm::perform(algorithm, testDataVector, outer_range, inner_range, args.treshold, length);
	Timer::instance().finishMeasure("Calculation time");
	
	// Print results
	for (unsigned int i = 0; i < groups.size(); i++) {
		cout << "Similar to " << inner_range[i] << ":" << endl;
		for (int id : groups[i]) {
			cout << id << endl;
		}
		cout << endl;
	}
	
	// Print timings
	for (auto &entry : Timer::instance().measures) {
		cout << entry.first << ": " << fixed << entry.second << " s" << endl;
	}
		
	return 0;
}

int parseCLIArguments(boost::program_options::variables_map &vm, CLIArguments &args, Algorithm::AlgorithmType &algorithm) {
	// Check if input file is provided
	if(!vm.count("input-data")) {
		cout << "No input file provided!" << endl;
		return 2;
	}

	// Check if treshold is provided
	if(!vm.count("treshold")) {
		cout << "[INFO] No treshold provided, setting to 0.9" << endl;
		args.treshold = 0.9;
	}

	// Check desired algorithm type
	algorithm = getAlgorithmType(args.algorithm, args.interpretation);
	if(algorithm == Algorithm::AlgorithmType::INVALID_TYPE) {
		return 3;
	}

	return 0;
}

Algorithm::AlgorithmType getAlgorithmType(string algorithm, string interpretation) {
	if(algorithm == "naive") {
		if(interpretation == "binary")
			return Algorithm::AlgorithmType::NAIVE_BINARY;
		else if(interpretation == "real")
			return Algorithm::AlgorithmType::NAIVE_REAL;
		else
			return Algorithm::AlgorithmType::INVALID_TYPE;
	}
	else if(algorithm == "triangle") {
		if(interpretation == "binary")
			return Algorithm::AlgorithmType::TRIANGLE_BINARY;
		else if(interpretation == "real")
			return Algorithm::AlgorithmType::TRIANGLE_REAL;
		else
			return Algorithm::AlgorithmType::INVALID_TYPE;
	}
	else
		return Algorithm::AlgorithmType::INVALID_TYPE;
}

SparseData makeSparseData(int id, double *tab, int length) {
	SparseData result;
	result.id = id;
	for (int i = 0; i < length; i++) {
		if (tab[i] != 0) {
			result.data.push_back(make_pair(i, tab[i]));
		}
	}
	return result;
}
