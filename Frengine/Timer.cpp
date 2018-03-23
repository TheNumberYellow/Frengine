#include "Timer.h"

using namespace FR;

// Instantiate static member variables
int64_t Timer::TICKS_PER_SECOND;
int64_t Timer::currTickCount;

void Timer::initTimer() {
	// Performance frequecy is fixed at system boot and is consistent across all processors
	QueryPerformanceFrequency((LARGE_INTEGER *)&TICKS_PER_SECOND);
	QueryPerformanceCounter((LARGE_INTEGER *)&currTickCount);

}

double Timer::getDeltaTime() {
	int64_t prevTickCount = currTickCount;

	QueryPerformanceCounter((LARGE_INTEGER *)&currTickCount);

	int64_t deltaTicks = currTickCount - prevTickCount;

	double deltaMillis = (double)(deltaTicks * (1000.0 / TICKS_PER_SECOND));
	double deltaSecs = deltaMillis / 1000.0;

	return deltaSecs;
}
