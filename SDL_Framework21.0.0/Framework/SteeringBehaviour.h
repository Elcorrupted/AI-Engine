#ifndef STEERINGBEHAVIOUR_H
#define STEERINGBEHAVIOUR_H
#include "Vector.h"
#include "VMath.h"
#include "Mouse.h"
#include "AICharacter.h"
#include "SteeringOutput.h"
#include "PhysicsComponent.h"

class SteeringBehaviour
{
protected:
	SteeringOutput* result = nullptr;
	AICharacter* character = nullptr;
public:
	virtual SteeringOutput* GetSteering() = 0;
};

#endif // !STEERINGBEHAVIOUR_H