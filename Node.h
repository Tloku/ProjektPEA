#pragma once
#include <iostream>
#include <vector>


class Node
{
public:
	std::vector<std::pair<int, int>> path;
	int** reducedMatrix;
	int cost;
	int vertex;
	int level;
	
	Node();
	Node* newNode(int**,int , std::vector<std::pair<int, int>> const&, int, int, int);
	void printPath(std::vector<std::pair<int, int>> const&);

};

