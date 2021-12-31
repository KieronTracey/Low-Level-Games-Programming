#include "Timing.h"
#include <iostream>



void Timing::TimerStart()
{
	TimerStartTime = chrono::steady_clock::now();
}

void Timing::TimerEnd()
{
	TimerEndTime = chrono::steady_clock::now();
}

void Timing::TimeTaken()
{
	UI ui;
	std::chrono::duration<double> diff = TimerEndTime - TimerStartTime;

	std::cout << "Time Taken: " << diff.count() << endl;
}

Timing::Timing()
{

}

Timing::~Timing()
{

}