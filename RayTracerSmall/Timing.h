#ifndef _TIMING_H_
#define _TIMING_H_
#include <string>
#include <chrono>

#include "UI.h"

using namespace std;
class Timing
{
public:
	Timing();
	~Timing();

	void StartTimer();
	void EndTimer();
	void PrintTimeTaken();

	string ms_uniqieID;
	chrono::steady_clock::time_point m_startTime;
	chrono::steady_clock::time_point m_endTime;
};

#endif // !_TIMING_H_