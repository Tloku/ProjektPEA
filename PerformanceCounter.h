#pragma once
#include<windows.h>

class PerformanceCounter
{
	double PCfreq;
	__int64 counterStart;

public:

	void startCounter();
	double getCounter();

};