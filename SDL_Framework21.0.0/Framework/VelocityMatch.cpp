#include "VelocityMatch.h"
#include "VMath.h"

VelocityMatch::VelocityMatch(Mouse* character_, Mouse* target_) : character(nullptr), target(nullptr) {
	character = character_;
	target = target_;
}

VelocityMatch::~VelocityMatch() {
	if (character) delete character;
	if (target) delete target;
}

SteeringOutput VelocityMatch::GetSteering() {
	SteeringOutput* result = new SteeringOutput();

	//Finding the difference between the target and the characters velocities
	result->linear = target->GetVel() - character->GetVel();
	//Increases the characters acceleration to approach the targets velocity
	result->linear /= timeToTarget;

	//Prevents the acceleration from going over the characters maxAcceleration
	if (VMath::mag(result->linear) > character->GetMaxAccel()) {
		result->linear = VMath::normalize(result->linear);
		result->linear *= character->GetMaxAccel();
	}

	result->angular = 0;
	return *result;
}