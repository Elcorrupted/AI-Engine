#ifndef ALIGN_H
#define ALIGN_H

#include "Mouse.h"
#include "Cheese.h"
#include "SteeringBehaviour.h"

class Align : public SteeringBehaviour{
public:
	//Change later
	Align();
	Align(AICharacter* character_, Cheese* target_);
	~Align();
	SteeringOutput* GetSteering();

protected:
	float targetOrietation;

	float timeToTarget;
	//Radius to say we have arrived at the target
	float targetRadius;
	//Radius to begin slowdown
	float slowRadius;
};
#endif // !ALIGN_H

