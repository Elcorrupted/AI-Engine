#include "AICharacter.h"

AICharacter::AICharacter() : Body(),  steering(new SteeringOutput()), health(2) {}

AICharacter::AICharacter(Vec3 pos_, float orientation_) : steering(new SteeringOutput()), health(2) {
	pos = pos_;
	orientation = orientation_;
}

AICharacter::~AICharacter() {
	if (steering) delete steering;
	for (Component* comp : components) {
		if (comp) delete comp;
		comp = nullptr;
	}
	components.clear();
}

void AICharacter::Update(float deltaTime, SteeringOutput* steering_) {
	*steering = *steering_;
	for (auto comp : components) {
		comp->Update(deltaTime);
	}
}