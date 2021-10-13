#include "PerformanceCounter.h"
#include <iostream>


void PerformanceCounter::startCounter()
{
	PCfreq = 0.0;
	counterStart = 0;
	LARGE_INTEGER li;
	if (!QueryPerformanceFrequency(&li))
		std::cout << "QueryPerformanceFrequency failed!\n";

	PCfreq = double(li.QuadPart) / 1000000.0;

	QueryPerformanceCounter(&li);
	counterStart = li.QuadPart;
}

double PerformanceCounter::getCounter()
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	return double(li.QuadPart - counterStart) / PCfreq;
}
