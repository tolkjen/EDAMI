#ifndef TIMER_H
#define TIMER_H

#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <ratio>
#include <chrono>

using namespace std;
using namespace std::chrono;

class Timer {
public:
	vector<pair<string, double>> measures;
	
public:	
	void startMeasure();
	void finishMeasure(string str);
	
	static Timer& instance();
	
private:
	static Timer *_instance;
	high_resolution_clock::time_point timeZero;
	
private:
	Timer();
};

#endif
