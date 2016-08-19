//
//  BenchmarkTimer.h
//  ModelView
//
//  Created by Bowen Yang on Aug 4, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# ifndef BENCHMARKTIMER
# define BENCHMARKTIMER

# ifdef _MSC_VER
# include <Windows.h>

class BenchmarkTimer
{
private:
	double frequency;
	__int64 startTime;
	__int64 endTime;
	bool isTimerStarted;
public:
	BenchmarkTimer()
	{
		LARGE_INTEGER temp;
		QueryPerformanceFrequency(&temp);
		this->frequency = temp.QuadPart;
		this->isTimerStarted = false;
	}
	void startTimer()
	{
		LARGE_INTEGER temp;
		this->isTimerStarted = true;
		QueryPerformanceCounter(&temp);
		this->startTime = temp.QuadPart;
	}
	void endTimer()
	{
		if (!this->isTimerStarted)
		{
			std::cout << "Timer not started yet" << std::endl;
			return;
		}
		LARGE_INTEGER temp;
		this->isTimerStarted = false;
		QueryPerformanceCounter(&temp);
		this->endTime = temp.QuadPart;
	}
	double getDeltaTimeInms()
	{
		return 1000 * ((this->endTime - this->startTime) / this->frequency);
	}
};
# else

class BenchmarkTimer
{
private:
	double frequency;
	__int64 startTime;
	__int64 endTime;
	bool isTimerStarted;
public:
	BenchmarkTimer()
	{
		LARGE_INTEGER temp;
		QueryPerformanceFrequency(&temp);
		this->frequency = temp.QuadPart;
		this->isTimerStarted = false;
	}
	void startTimer()
	{
		LARGE_INTEGER temp;
		this->isTimerStarted = true;
		QueryPerformanceCounter(&temp);
		this->startTime = temp.QuadPart;
	}
	void endTimer()
	{
		if (!this->isTimerStarted)
		{
			std::cout << "Timer not started yet" << std::endl;
			return;
		}
		LARGE_INTEGER temp;
		this->isTimerStarted = false;
		QueryPerformanceCounter(&temp);
		this->endTime = temp.QuadPart;
	}
	double getDeltaTimeInms()
	{
		return 1000 * ((this->endTime - this->startTime) / this->frequency);
	}
};

# endif

extern BenchmarkTimer GlobalTimer;
# endif