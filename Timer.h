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

/*
 * Singleton class used to measure time of activities (eg. performing 
 * calculations, loading data from files). 
 */
class Timer {
public:
	/*
	 * @brief Holds pairs of description and time of activities.
	 */
	vector<pair<string, double>> measures;
	
public:	
	/*
	 * @brief Starts time measurement. 
	 */
	void startMeasure();
	
	/*
	 * @brief Finishes time measurement and assigns a description to it.
	 * 
	 * @param str Description of time measurement.
	 */
	void finishMeasure(string str);
	
	/*
	 * @brief Finishes measurement and returns a time value.
	 */
	double finishMeasure();
	
	/*
	 * @brief Gives an instance of singleton. Use it to access methods.
	 */
	static Timer& instance();
	
private:
	static Timer *_instance;
	high_resolution_clock::time_point timeZero;
	
private:
	Timer();
};

#endif
