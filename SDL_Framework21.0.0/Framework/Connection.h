#ifndef CONNECTION_H
#define CONNECTION_H

#include "Node.h"

class Connection {
private:
	Node currentNode;
	Node toNode;

	//need to change and the get
	float cost;

public:
	inline float GetCost() { return cost; }
};
#endif // !CONNECTION_H

