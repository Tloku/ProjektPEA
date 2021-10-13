#pragma once
#include "Edge.h"
class AdjacencyMatrix
{
public:
	int x;
	int** V;
	AdjacencyMatrix(int);
	AdjacencyMatrix();
	void addEdge(int i, int j, int weight);
	void displayMatrix();
};

