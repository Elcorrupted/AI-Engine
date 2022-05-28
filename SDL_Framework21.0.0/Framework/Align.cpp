#include "Align.h"
#include "VMath.h"

Align::Align() : targetOrietation(0.0f),
				 timeToTarget(0.1f), targetRadius(0.0f), slowRadius(M_PI / 4) {
}

Align::Align(AICharacter *character_, Cheese* target_) : targetOrietation(target_->GetOrientation()), timeToTarget(0.1f), targetRadius(0.0f), slowRadius(1.0f) {
	character = character_;
	targetOrietation = target_->GetOrientation();
}

Align::~Align() {
	if (character) delete character;
	if (result) delete result;
}

SteeringOutput* Align::GetSteering() {
	result = new SteeringOutput();

	//Get rotation difference between target orientation and current orientation
	float rotation = targetOrietation - character->GetOrientation();

	//Used to clamp the rotation down to between -pi and pi
	//Bellow is what mapToRange does
	rotation = std::fmodf(rotation, 2 * M_PI);
	if (rotation < -M_PI) {
		rotation += 2 * M_PI;
	}
	else if (rotation >= M_PI) {
		rotation -= 2 * M_PI;
	}

	float rotationSize = abs(rotation);
	float targetRotation;

	//Within target radius. No rotation from this algorithm
	if (rotationSize < targetRadius) {
		return result;
	}
	//Outside slow radius use the max rotation of character
	else if (rotationSize > slowRadius) {
		targetRotation = character->GetComponent<PhysicsComponent>()->GetMaxRot();
	}
	//Within slow radius, so adjust accordingly
	else {
		targetRotation = character->GetComponent<PhysicsComponent>()->GetMaxRot() * rotationSize / slowRadius;
	}

	//Figures out which direction the rotation needs to go (left/right)
	targetRotation *= rotation / rotationSize;

	//Creates the desired change in angular motion
	result->angular = targetRotation - character->GetComponent<PhysicsComponent>()->GetRot();
	result->angular /= timeToTarget;

	//Makes sure we do not exceed the maximum rotation of the character
	float angularAcc = abs(result->angular);
	if (angularAcc > character->GetComponent<PhysicsComponent>()->GetMaxRot()) {
		result->angular /= angularAcc;
		result->angular *= character->GetComponent<PhysicsComponent>()->GetMaxRot();
	}

	result->linear = Vec3();
	return result;
}