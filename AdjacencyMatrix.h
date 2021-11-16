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

	std::vector<int> nodePath;
	int **nodeReducedMatrix;
	int nodeCost;
	int nodeVertex;
	int nodeLevel;
	int* minRow;
	int* minCol;
	int** initNodeMatrix(int** nodeReducedMatrix);
	AdjacencyMatrix* newNode(int **, std::vector<int> const& , int , int, int);
	
	AdjacencyMatrix(int);
	AdjacencyMatrix();
	void addEdge(int i, int j, int weight);
	void displayMatrix();
	int minimalizeMatrix(int **V);
	void TSPbruteForce();
	int branchAndBound();
	void printPath(std::vector<int> const&);
	int heldKarp(int**, int, int, std::vector<std::vector<int>>&);
	int startHeldKarp();
};

