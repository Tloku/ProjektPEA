#pragma once
#include "Edge.h"
#include <iostream>
#include <vector>
#include <algorithm>


class AdjacencyMatrix
{
public:
	int x;
	int** V;
	std::vector<int> vertex;
	int min_weight;
	int current_pathweight;

	AdjacencyMatrix(int);
	AdjacencyMatrix();
	void addEdge(int i, int j, int weight);
	void displayMatrix();

	void TSPbruteForce();
};

