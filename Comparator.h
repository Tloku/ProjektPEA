#pragma once
#include "AdjacencyMatrix.h"

struct Comparator {
	bool operator()(const AdjacencyMatrix* left, const AdjacencyMatrix* right) const {
		return left->nodeCost > right->nodeCost;
	}
};