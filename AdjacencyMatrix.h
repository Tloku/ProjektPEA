#pragma once
#include <algorithm>
#include "Edge.h"
#include "PerformanceCounter.h"
#include <iostream>
#include <vector>
#include <iomanip> 

class AdjacencyMatrix
{
public:
	int x;
	int** V;
	std::vector<int> vertex;
	std::vector<int> path;
	int min_weight;
	int current_pathweight;
	PerformanceCounter counter;
	double timer;

	AdjacencyMatrix(int);
	AdjacencyMatrix();
	void addEdge(int i, int j, int weight);
	void displayMatrix();

	void TSPbruteForce();
};

