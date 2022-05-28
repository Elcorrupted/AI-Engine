#ifndef DYNAMICARRIVE_H
#define DYNAMICARRIVE_H

#include "Vector.h"
#include "VMath.h"
#include "SteeringBehaviour.h"

using namespace MATH;

class DynamicArrive: public SteeringBehaviour
{
protected:
	Vec3 targetPos;
	float timeToTarget, targetRadius, slowRadius;
public:
	DynamicArrive();
	DynamicArrive(AICharacter* character_, Vec3 pos_, float timeToTarget_, float targetRadius_, float slowRadius_);
	~DynamicArrive();
	SteeringOutput* GetSteering();
};

#endif // !DYNAMICARRIVE_H
