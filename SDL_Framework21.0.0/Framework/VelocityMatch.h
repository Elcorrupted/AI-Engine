#ifndef VELOCITYMATCH_H
#define VELOCITYMATCH_H

#include "Mouse.h"
#include "Cheese.h"

class VelocityMatch {
public:
	//Change later
	VelocityMatch(Mouse* character_, Mouse* target_);
	~VelocityMatch();
	SteeringOutput GetSteering();


private:
	Mouse* character;
	Mouse* target;

	float timeToTarget = 0.1f;
};
#endif // !VELOCITYMATCH_H

