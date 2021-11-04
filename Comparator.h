#pragma once
#include "Node.h"

struct Comparator {
	bool operator()(const Node* left, const Node* right) const {
		return left->cost > right->cost;
	}
};