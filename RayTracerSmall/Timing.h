#ifndef _TIMING_H_
#define _TIMING_H_

#include "UI.h"
#include <chrono>
#include <string>

class Timing
{
public:

	string ID;
	chrono::steady_clock::time_point TimerStartTime;
	chrono::steady_clock::time_point TimerEndTime;

	Timing();
	~Timing();

	void TimeTaken();
	void TimerStart();
	void TimerEnd();
};

#endif