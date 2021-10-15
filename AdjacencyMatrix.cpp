#include "AdjacencyMatrix.h"

AdjacencyMatrix::AdjacencyMatrix() {}

AdjacencyMatrix::AdjacencyMatrix(int x)
{
	this->x = x;
	V = new int*[x];
	min_weight = INT_MAX;

	for (int i = 0; i < x; i++)
		V[i] = new int[x];

	for (int i = 0; i < x; i++)
		for (int j = 0; j < x; j++)
			V[i][j] = 0;
}

void AdjacencyMatrix::addEdge(int i, int j, int weight)
{
	V[i][j] = weight;
}

void AdjacencyMatrix::displayMatrix()
{
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < x; j++)
		{
			if (V[i][j] == INT_MAX)
				std::cout << "0 ";
			else
				std::cout << V[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void AdjacencyMatrix::TSPbruteForce()
{
	int k = 0;
	//store all vertexes beside first one "0"
	for (int i = 1; i < x; i++)
		vertex.push_back(i);

	do{
		current_pathweight = 0;
		k = 0;
		for (int i = 0; i < vertex.size(); i++)
		{
			current_pathweight += V[k][vertex[i]];
			k = vertex[i];
		}
		current_pathweight += V[k][0];
		min_weight = std::min(current_pathweight, min_weight);

	} while (std::next_permutation(vertex.begin(), vertex.end()));

	std::cout << "MinPath: " << min_weight;
}
