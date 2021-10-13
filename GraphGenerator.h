#pragma once
#include "Edge.h"
#include "AdjacencyMatrix.h"
#include <Windows.h>

class GraphGenerator
{
public:
	int number_of_nodes;
	int max_number_of_edges;

	GraphGenerator(int);
	GraphGenerator();
	void generateGraph(AdjacencyMatrix, float);
	void generateGraphMST(AdjacencyMatrix, float);
};

