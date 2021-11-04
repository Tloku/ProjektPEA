#pragma once
#include <algorithm>
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
	bool* visited;
	int min_weight;
	int current_pathweight;
	PerformanceCounter counter;
	double timer;
	int reducedCost;
	std::vector<int> currentPath;
	int currentWeight;
	int currentBound;

	AdjacencyMatrix(int);
	AdjacencyMatrix();
	void addEdge(int i, int j, int weight);
	void displayMatrix();
	int minimalizeMatrix(int **V);
	void TSPbruteForce();
	void branchAndBound();
	int findMin(int);
	void printPath(std::vector<std::pair<int, int>> const&);
	/*void rowReduction(int [], int);
	void columnReduction(int [], int);
	int calculateCost()*/;
};

