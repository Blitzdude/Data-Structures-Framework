#pragma once

class Timer
{
	// performance counter
	LARGE_INTEGER frequency;        // ticks per second
	LARGE_INTEGER t1, t2;           // ticks

public:
	double elapsedTime;

	void Start()
	{
		// get ticks per second
		QueryPerformanceFrequency( &frequency );

		// start timer
		QueryPerformanceCounter( &t1 );
	}

	double GetDuration()
	{
		// stop timer
		QueryPerformanceCounter( &t2 );

		// compute and print the elapsed time in millisec
		elapsedTime = ( t2.QuadPart - t1.QuadPart ) * 1000.0 / frequency.QuadPart;
		return elapsedTime;
	}
};
