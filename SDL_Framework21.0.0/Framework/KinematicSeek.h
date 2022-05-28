#ifndef KINEMATICSEEK_H
#define KINEMATICSEEK_H


#include "Vector.h"
#include "VMath.h"
#include "KinematicSteeringOutPut.h"
#include "Mouse.h"
using namespace MATH;

class KinematicSeek
{
private:
	KinematicSteeringOutPut* result;
	Mouse* character;
	Vec3 target;

public:
	KinematicSeek(Mouse* character_, Vec3 target_);
	~KinematicSeek();
	KinematicSteeringOutPut getSteering();
};

#endif // !KINEMATICSEEK_H