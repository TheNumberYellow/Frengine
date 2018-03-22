#pragma once

#include <Windows.h>
#include <stdint.h>

namespace FR {
	class Timer {
	public:
		static void initTimer();

		// Returns time in seconds since last call of getDeltaTime() or initTimer()
		static double getDeltaTime();


	private:
		static int64_t TICKS_PER_SECOND;
		static int64_t currTickCount;
	};
}
