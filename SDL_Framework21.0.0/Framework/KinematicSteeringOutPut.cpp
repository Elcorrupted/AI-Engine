#include "KinematicSteeringOutPut.h"

KinematicSteeringOutPut::KinematicSteeringOutPut()
{
	velocity = Vec3(0.0f, 0.0f, 0.0f);
	rotation = 0.0f;
}

KinematicSteeringOutPut::~KinematicSteeringOutPut()
{
}

KinematicSteeringOutPut::KinematicSteeringOutPut(Vec3 velocity_, float rotation_)
{
	velocity = velocity_;
	rotation = rotation_;
}
