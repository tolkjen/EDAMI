#include "Timer.h"

using namespace std;
using namespace std::chrono;

Timer* Timer::_instance = 0;

Timer::Timer()
{
}

void Timer::startMeasure() {
	timeZero = high_resolution_clock::now();
}

void Timer::finishMeasure(string str) {
	high_resolution_clock::time_point timeNow = high_resolution_clock::now();
	duration<double> time_span = duration_cast<duration<double>>(timeNow - timeZero);
	measures.push_back( make_pair(str, time_span.count()) );
}

double Timer::finishMeasure() {
	high_resolution_clock::time_point timeNow = high_resolution_clock::now();
	duration<double> time_span = duration_cast<duration<double>>(timeNow - timeZero);
	return time_span.count();
}

Timer& Timer::instance() {
	if (_instance == 0) {
		_instance = new Timer();
	}
	return *_instance;
}
