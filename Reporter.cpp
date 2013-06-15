#include "Reporter.h"

Reporter* Reporter::_instance = 0;

Reporter::Reporter() 
{
}

Reporter& Reporter::instance() 
{
	if (_instance == 0)
		_instance = new Reporter();
	return *_instance;
}

void Reporter::addReport(string s) 
{
	reports.push_back(s);
}
