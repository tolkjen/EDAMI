#ifndef REPORTER_H
#define REPORTER_H

#include <vector>
#include <string>

using namespace std;

class Reporter {
public:
	vector<string> reports;
	
public:
	void addReport(string s);
	static Reporter& instance();
	
private:
	static Reporter *_instance;
	
private:
	Reporter();
};

#endif
