#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <boost/program_options.hpp>

#include "Algorithm.h"
#include "Timer.h"
#include "IReader.h"
#include "InternetDataReader.h"
#include "RangeParser.h"

using namespace std;
namespace opt = boost::program_options;

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
 * @param algorithmType Algorithm type that should be used in execution.
 * @param readMode Mode of interpreting input data.
 * @return Error code
 */
int parseCLIArguments(opt::variables_map &vm, CLIArguments &args, Algorithm::AlgorithmType &algorithmType, IReader::ReadMode &readMode);

/*
 * @brief Returns algorithm type basing on user preferences.
 *
 * @param algorithm Algorithm name that should be used in execution.
 * @param interpretation Method of data interpretation.
 * @return Algorithm type.
 */
Algorithm::AlgorithmType getAlgorithmType(string algorithm, string interpretation);

/*
 * @brief Returns input data read mode basing on user preferences.
 *
 * @param interpretation Method of data interpretation.
 * @return Read mode.
 */
IReader::ReadMode getReadMode(string interpretation);

/*
 * OBSOLETE: to be removed
 */
SparseData makeSparseData(int id, double *tab, int length);

int main(int argc, char *argv[]) {
	CLIArguments args;
	IReader::ReadMode readMode;

	// Collect CLI arguments
	opt::options_description options("Options");
	options.add_options()
		("help,h", "print help message")
		("input-data,d", opt::value<string>(&args.inputFile), "file with input data (-d flag can be omitted)")
		("target-set,r", opt::value<string>(&args.targetSet)->default_value("1"), "number of rows defining set for which similar vectors will be searched")
		("search-set,s", opt::value<string>(&args.searchSet)->default_value("all"), "number of rows defining set where similar vectors will be searched")
		("algorithm,a", opt::value<string>(&args.algorithm)->default_value("triangle"), "search algorithm")
		("interpretation,i", opt::value<string>(&args.interpretation)->default_value("real"), "data interpretation method")
		("treshold,t", opt::value<double>(&args.treshold), "Tanimoto similarity threshold value")
	;

	opt::positional_options_description defaultOption;
	defaultOption.add("input-data", 1);

	opt::variables_map vm;
	try {
		opt::store(opt::command_line_parser(argc, argv).options(options).positional(defaultOption).run(), vm);
		opt::notify(vm);
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
	vector<int> targetRows = RangeParser::parseRowRanges(args.targetSet);
	vector<int> searchRows = RangeParser::parseRowRanges(args.searchSet);

	Algorithm::AlgorithmType algorithm;
	int ret = parseCLIArguments(vm, args, algorithm, readMode);
	if(ret != 0) {
		return ret;
	}

	// Prepare input data
	IReader *dataReader = new InternetDataReader();
	vector<SparseData> dataVector = dataReader->read(args.inputFile, readMode);

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
	//auto groups = Algorithm::perform(algorithm, dataVector, outer_range, inner_range, args.treshold, dataReader->attributeCount());
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

int parseCLIArguments(opt::variables_map &vm, CLIArguments &args, Algorithm::AlgorithmType &algorithmType, IReader::ReadMode &readMode) {
	// Check if input file is provided
	if(!vm.count("input-data")) {
		cout << "[ERROR] No input file provided!" << endl;
		return 2;
	}

	// Check if treshold is provided
	if(!vm.count("treshold")) {
		args.treshold = 0.9;
	}

	// Check desired algorithm type
	algorithmType = getAlgorithmType(args.algorithm, args.interpretation);
	if(algorithmType == Algorithm::INVALID_TYPE) {
		return 3;
	}

	// Check desired read mode
	readMode = getReadMode(args.interpretation);
	if(readMode == IReader::INVALID_MODE) {
		return 4;
	}

	return 0;
}

Algorithm::AlgorithmType getAlgorithmType(string algorithm, string interpretation) {
	if(algorithm == "naive") {
		if(interpretation == "binary")
			return Algorithm::NAIVE_BINARY;
		else if(interpretation == "real")
			return Algorithm::NAIVE_REAL;
		else
			return Algorithm::INVALID_TYPE;
	}
	else if(algorithm == "triangle") {
		if(interpretation == "binary")
			return Algorithm::TRIANGLE_BINARY;
		else if(interpretation == "real")
			return Algorithm::TRIANGLE_REAL;
		else
			return Algorithm::INVALID_TYPE;
	}
	else
		return Algorithm::INVALID_TYPE;
}

IReader::ReadMode getReadMode(string interpretation) {
	if(interpretation == "real") {
		return IReader::REAL;
	}
	else if(interpretation == "binary") {
		return IReader::BINARY;
	}
	else
		return IReader::INVALID_MODE;
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
