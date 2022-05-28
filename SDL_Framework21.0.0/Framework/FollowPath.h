#ifndef FOLLOWPATH_H
#define FOLLOWPATH_H

#include "DynamicArrive.h"
#include "LookWhereYoureGoing.h"
#include "Node.h"
#include <vector>

class FollowPath : public DynamicArrive {
private:
	std::vector<Node> path;

public:
	FollowPath(AICharacter* character_, float timeToTarget_, float targetRadius_, float slowRadius_, std::vector<Node> path_);
	SteeringOutput* GetSteering();
};

#endif // !FOLLOWPATH_H
