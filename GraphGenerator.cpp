#include "GraphGenerator.h"
#include <time.h>

GraphGenerator::GraphGenerator(){}

GraphGenerator::GraphGenerator(int number_of_nodes)
{
	this->number_of_nodes = number_of_nodes;
	this->max_number_of_edges = (number_of_nodes * (number_of_nodes - 1)) / 2;
}

void GraphGenerator::generateGraph(AdjacencyMatrix mat, float percentage)
{
	srand(time(NULL));
	int number_of_edges = max_number_of_edges * percentage;
	bool generated = false;
	int begin_vertex;
	int end_vertex;
	int weight;
	int i;

	for (i = 0; i < number_of_nodes - 1; i++)
	{
		if (number_of_edges != 0)
		{
			weight = (rand() % 100) - 15;
			mat.addEdge(i, i + 1, weight);
			number_of_edges--;
		}
		
	}
	if (number_of_edges != 0)
	{
		weight = (rand() % 100) - 15;
		mat.addEdge(i, i - 2, weight);
		number_of_edges--;
	}

	if (number_of_edges != 0)
	{
		while (!generated)
		{
			begin_vertex = rand() % number_of_nodes;
			end_vertex = rand() % number_of_nodes;
			weight = (rand() % 100) - 15;

			if (begin_vertex != end_vertex && mat.V[begin_vertex][end_vertex] == INT_MAX)
			{
				mat.addEdge(begin_vertex, end_vertex, weight);
				number_of_edges--;
			}

			if (number_of_edges == 0)
				generated = true;
		}
	}
}

void GraphGenerator::generateGraphMST(AdjacencyMatrix mat, float percentage)
{
	srand(time(NULL));
	int number_of_edges = max_number_of_edges * percentage;
	bool generated = false;
	int begin_vertex;
	int end_vertex;
	int weight;
	int i;

	for (i = 0; i < number_of_nodes - 1; i++)
	{
		if (number_of_edges != 0)
		{
			weight = (rand() % 100);
			mat.addEdge(i, i + 1, weight);
			mat.addEdge(i + 1, i, weight);
			number_of_edges--;
		}
	}

	if (number_of_edges != 0)
	{
		weight = (rand() % 100);
		mat.addEdge(i, i - 2, weight);
		mat.addEdge(i - 2, i, weight);
		number_of_edges--;
	}

	if (number_of_edges != 0)
	{
		while (!generated)
		{
			begin_vertex = rand() % number_of_nodes;
			end_vertex = rand() % number_of_nodes;
			weight = (rand() % 100);

			if (begin_vertex != end_vertex && mat.V[begin_vertex][end_vertex] == INT_MAX)
			{
				mat.addEdge(begin_vertex, end_vertex, weight);
				mat.addEdge(end_vertex, begin_vertex, weight);
				number_of_edges--;
			}

			if (number_of_edges == 0)
				generated = true;
		}
	}
}