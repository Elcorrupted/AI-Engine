#ifndef KINEMATICSTEERINGOUTPUT_H
#define KINEMATICSTEERINGOUTPUT_H

#include "Vector.h"
using namespace MATH;

class KinematicSteeringOutPut
{
public:
	Vec3 velocity;
	float rotation;

	KinematicSteeringOutPut();
	~KinematicSteeringOutPut();

	KinematicSteeringOutPut(Vec3 velocity_, float rotation_);

};

#endif