#include "LookWhereYoureGoing.h"
#include "VMath.h"

LookWhereYoureGoing::LookWhereYoureGoing(AICharacter* character_)  {
	character = character_;
}

LookWhereYoureGoing::~LookWhereYoureGoing() {
	if (character) delete character;
	if (result) delete result;
}

SteeringOutput* LookWhereYoureGoing::GetSteering() {
	result = new SteeringOutput();
	
	//Check for zero direction first
	Vec3 velocity = character->GetComponent<PhysicsComponent>()->GetVel();
	if (VMath::mag(velocity) == 0.0f) {
		return result;
	}

	//Calculate the target to delegate to Align
	targetOrietation = atan2(-velocity.x, -velocity.y);

	//Use aligns GetSteering()
	return Align::GetSteering();
}