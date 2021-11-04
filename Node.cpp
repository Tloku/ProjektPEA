#include "Node.h"
#include "AdjacencyMatrix.h"


Node::Node()
{
	reducedMatrix = new int* [5];

	for (int i = 0; i < 5; i++)
		reducedMatrix[i] = new int[5];

	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			reducedMatrix[i][j] = 0;
}


Node* Node::newNode(int **matrixToBeReduced, int size, std::vector<std::pair<int, int>> const & path, int level, int i, int j)
{
	Node* node = new Node;

	node->path = path;
	
	if (level == 0){
		node->path.push_back(std::make_pair(i, j));
	}

	memcpy(node->reducedMatrix, matrixToBeReduced, sizeof node->reducedMatrix);

	for (int k = 0; k < size && level != 0; k++)
	{
		node->reducedMatrix[i][k] = INT_MAX;
		node->reducedMatrix[k][j] = INT_MAX;
	}
	
	node->reducedMatrix[j][0] = INT_MAX;
	node->level = level;
	node->vertex = j;

	return node;
}