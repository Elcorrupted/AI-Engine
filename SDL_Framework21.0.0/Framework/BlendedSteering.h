#ifndef BLENDEDSTEERING_H
#define BLENDEDSTEERING_H

#include "SteeringBehaviour.h"
#include <vector>

struct BehaviourAndWeight
{
	BehaviourAndWeight(SteeringBehaviour* behaviour_, float weight_) { behaviour = behaviour_; weight = weight_; }
	~BehaviourAndWeight() { if (behaviour) delete behaviour; }

	float weight;
	SteeringBehaviour* behaviour;
};

class BlendedSteering : public SteeringBehaviour {
public:
	BlendedSteering(AICharacter* character_);
	~BlendedSteering();

	SteeringOutput* GetSteering();

	void AddBehaviour(SteeringBehaviour* behaviour_, float weight_);
	void RemoveBehaviour(SteeringBehaviour* behaviour_, float weight_);

private:
	std::vector<BehaviourAndWeight*> behaviours;
};
#endif // !BLENDEDSTEERING_H
