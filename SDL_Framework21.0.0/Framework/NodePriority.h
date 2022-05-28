#ifndef NODEPRIORITY_H
#define NODEPRIORITY_H

#include "Node.h"

class NodePriority {
public:
	Node* node;
	float priority;

	inline NodePriority(Node* node_, float priority_) {
		node = node_;
		priority = priority_;
	}
};
#endif // !NODEPRIORITY_H

