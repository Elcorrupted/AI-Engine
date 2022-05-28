#ifndef KINEMATICARRIVE_H
#define KINEMATICARRIVE_H

#include "Vector.h"
#include "VMath.h"
#include "Mouse.h"
#include "KinematicSteeringOutPut.h"
using namespace MATH;

class KinematicArrive
{
private:
	KinematicSteeringOutPut* result;
	Mouse* character;
	Vec3 target;
	float radius;
	float timeToTarget;
public:
	KinematicArrive(Mouse* character_, Vec3 target_, float radius_, float timeToTarget_);
	~KinematicArrive();
	KinematicSteeringOutPut GetSteering();
};

#endif // !KINEMATICARRIVE_H