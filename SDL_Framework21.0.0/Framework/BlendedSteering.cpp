#include "BlendedSteering.h"
#include <algorithm>

BlendedSteering::BlendedSteering(AICharacter* mouse_) {
	character = mouse_;
	behaviours.reserve(10);
}

BlendedSteering::~BlendedSteering() {
	for (auto &b : behaviours) {
		if (b->behaviour) delete b->behaviour;
		if (b) delete b;
	}
	behaviours.clear();
}

SteeringOutput* BlendedSteering::GetSteering() {
	result = new SteeringOutput();

	for (int i = 0; i < behaviours.size(); i++) {
		if (behaviours[i]->behaviour->GetSteering() != nullptr) {
			//Runs the behaviours and adds them to a new SteeringOutput that combines all behaviours
			*result += *behaviours[i]->behaviour->GetSteering() * behaviours[i]->weight;
		}
	}

	if (VMath::mag(result->linear) > character->GetComponent<PhysicsComponent>()->GetMaxAccel()) {
		result->linear = VMath::normalize(result->linear);
		result->linear *= character->GetComponent<PhysicsComponent>()->GetMaxAccel();
	}

	result->angular = std::min(result->angular, character->GetComponent<PhysicsComponent>()->GetMaxRot());
	return result;
}

void BlendedSteering::AddBehaviour(SteeringBehaviour* behaviour_, float weight_) {
	behaviours.push_back(new BehaviourAndWeight(behaviour_, weight_));
}

void BlendedSteering::RemoveBehaviour(SteeringBehaviour* behaviour_, float weight_) {
	int i = 0;
	for (auto &b : behaviours) {
		i++;
		if (b->behaviour == behaviour_ && b->weight == weight_) {
			behaviours[i]->behaviour = nullptr;
			behaviours.erase(behaviours.begin() + i);
			return;
		}
	}
}