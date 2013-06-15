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
#include "Reporter.h"

using namespace std;
namespace opt = boost::program_options;

/*
 * Holds CLI arguments provided by user.
 */
struct CLIArguments {
	string inputFile;
	string searchForSet;
	string searchWithinSet;
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
 * @return Error code
 */
int parseCLIArguments(opt::variables_map &vm, CLIArguments &args, Algorithm::AlgorithmType &algorithmType);

/*
 * @brief Returns algorithm type basing on user preferences.
 *
 * @param algorithm Algorithm name that should be used in execution.
 * @param interpretation Method of data interpretation.
 * @return Algorithm type.
 */
Algorithm::AlgorithmType getAlgorithmType(string algorithm, string interpretation);

int main(int argc, char *argv[]) {
	// Collect CLI arguments
	CLIArguments args;
	opt::options_description options("Options");
	options.add_options()
		("help,h", "print help message")
		("input-data,d", opt::value<string>(&args.inputFile), "file with input data (-d flag can be omitted)")
		("search-for,r", opt::value<string>(&args.searchForSet)->default_value("1"), "rows numbers defining set for which similar vectors will be searched")
		("search-within,s", opt::value<string>(&args.searchWithinSet)->default_value("all"), "rows numbers defining set where similar vectors will be searched")
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

	// Check CLI arguments
	Algorithm::AlgorithmType algorithm;
	int ret = parseCLIArguments(vm, args, algorithm);
	if(ret != 0) {
		return ret;
	}

	// Read input data
	IReader *dataReader = new InternetDataReader();
	vector<SparseData> dataVector = dataReader->read(args.inputFile);

	// Check ranges
	vector<int> searchForRows;
	vector<int> searchWithinRows;

	if(args.searchForSet != "all") {
		searchForRows = RangeParser::parseRowRanges(args.searchForSet);
	}
	else {
		searchForRows = RangeParser::rangeToRows("0-" + to_string(dataVector.size() - 1));
	}

	if(args.searchWithinSet != "all") {
		searchWithinRows = RangeParser::parseRowRanges(args.searchWithinSet);
	}
	else {
		searchWithinRows = RangeParser::rangeToRows("0-" + to_string(dataVector.size() - 1));
	}
	
	// Basic information about data
	cout << "Data rows: " << dataVector.size() << endl;
	cout << "Attributes: " << dataReader->attributeCount() << endl;
	cout << endl;

	// Algorithm
	auto groups = Algorithm::perform(algorithm, dataVector, searchWithinRows, searchForRows, args.treshold, dataReader->attributeCount());
	
	// Print reported messages
	for (auto &entry : Reporter::instance().reports)
		cout << entry << endl;
	
	// Print results
	for (unsigned int i = 0; i < groups.size(); i++) {
		cout << "Similar to " << searchForRows[i] << " (" << groups[i].size() << " found):" << endl;
		for (int id : groups[i]) {
			cout << id << endl;
		}
		cout << endl;
	}
		
	return 0;
}

int parseCLIArguments(opt::variables_map &vm, CLIArguments &args, Algorithm::AlgorithmType &algorithmType) {
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
