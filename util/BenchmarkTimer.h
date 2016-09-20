//
//  BenchmarkTimer.h
//  ModelView
//
//  Created by Bowen Yang on Aug 4, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# ifndef __ModelView__BenchmarkTimer__
# define __ModelView__BenchmarkTimer__

# ifdef _MSC_VER//On windows platform.
# include <Windows.h>

/**
@brief Timer object serving as an utility benchmark timer. 
*/
class BenchmarkTimer
{
private:
	/*
	CPU frequency.
	*/
	long long frequency;
	/*
	Start time.
	*/
	__int64 startTime;
	/*
	End time.
	*/
	__int64 endTime;
	/*
	Has the timer been started yet?
	*/
	bool isTimerStarted;
public:
	/**
	@brief Default constructor.
	*/
	BenchmarkTimer() : isTimerStarted(false)
	{
		LARGE_INTEGER temp;
		QueryPerformanceFrequency(&temp);
		this->frequency = temp.QuadPart;
	}
	/**
	@brief Start the benchmark timer.
	*/
	void startTimer()
	{
		LARGE_INTEGER temp;
		this->isTimerStarted = true;
		QueryPerformanceCounter(&temp);
		this->startTime = temp.QuadPart;
	}
	/**
	@brief End the benchmark timer.
	*/
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
	/**
	@brief Get the time elapsed in milliseconds.
	*/
	double getDeltaTimeInms()
	{
		return 1000.0 * (static_cast<double>(this->endTime - this->startTime) / this->frequency);
	}
};
# else//On Unix-like platforms.

# include <sys/time.h>

class BenchmarkTimer
{
private:
	timeval timer;
	bool isTimerStarted;
	long sec;
	long usec;
	long esec;
	long eusec;
public:
	BenchmarkTimer() : isTimerStarted(false)
	{
		
	}
	void startTimer()
	{
		this->isTimerStarted = true;
		gettimeofday(&timer, nullptr);
		this->sec = timer.tv_sec;
		this->usec = timer.tv_usec;
	}
	void endTimer()
	{
		if (!this->isTimerStarted)
		{
			std::cout << "Timer not started yet" << std::endl;
			return;
		}
		this->isTimerStarted = false;
		gettimeofday(&timer, nullptr);
		this->esec = timer.tv_sec;
		this->eusec = timer.tv_usec;
	}
	double getDeltaTimeInms()
	{
		return 1000.0 * (esec - sec) + (eusec - usec) / 1000.0;
	}
};

# endif

extern BenchmarkTimer GlobalTimer;
# endif