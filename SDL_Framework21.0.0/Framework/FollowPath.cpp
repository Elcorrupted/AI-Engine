#include "FollowPath.h"

FollowPath::FollowPath(AICharacter* character_, float timeToTarget_, float targetRadius_, float slowRadius_, std::vector<Node> path_) {
	character = character_;
	timeToTarget = timeToTarget_;
	targetRadius = targetRadius_;
	slowRadius = slowRadius_;
	path = path_;
}

SteeringOutput* FollowPath::GetSteering() {
	//Nothing left in path. Return null so the AI(mouse) will stop
	if (path.empty()) {
		return nullptr;
	}
	//Changes the targeted position for use in the DynamicArrive algorithm to be the one at the front of the optimal path
	targetPos = path.front().GetPos();
	//Runs the dynamic arrive steering algorithm
	result = DynamicArrive::GetSteering();
	//If reached the targetPos erase the node at the start of the path vector, so we can move onto the next node in the path
	if (result == NULL) {
		path.erase(path.begin());
	}
	//Returns the resulting Output for use by the AI(mouse) update
	return result;
}