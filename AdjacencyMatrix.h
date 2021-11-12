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

	std::vector<std::pair<int, int>> nodePath;
	int **nodeReducedMatrix;
	int nodeCost;
	int nodeVertex;
	int nodeLevel;
	int** initNodeMatrix(int** nodeReducedMatrix);
	AdjacencyMatrix* newNode(int **, std::vector<std::pair<int, int>> const& , int , int, int);
	AdjacencyMatrix* newMinNode(int** parentMatrix, std::vector<std::pair<int, int>> const& path, int level, int j);
	
	AdjacencyMatrix(int);
	AdjacencyMatrix();
	void addEdge(int i, int j, int weight);
	void displayMatrix();
	int minimalizeMatrix(int **V);
	void TSPbruteForce();
	int branchAndBound();
	int findMin(int);
	void printPath(std::vector<std::pair<int, int>> const&);
	int heldKarp(int**, int, int, std::vector<std::vector<int>>&);
	void startHeldKarp();
	/*void rowReduction(int [], int);
	void columnReduction(int [], int);
	int calculateCost()*/;
};

