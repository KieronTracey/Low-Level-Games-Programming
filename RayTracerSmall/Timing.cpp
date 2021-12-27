#include "Timing.h"
#include <iostream>

Timing::Timing()
{

}

Timing::~Timing()
{

}

void Timing::StartTimer()
{
	m_startTime = chrono::steady_clock::now();
}

void Timing::EndTimer()
{
	m_endTime = chrono::steady_clock::now();
}

void Timing::PrintTimeTaken()
{
	std::chrono::duration<double> l_diff = m_endTime - m_startTime;
	UI ui;
	cout << "Time Taken: " << l_diff.count() << "\n";
}