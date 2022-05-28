#include "KinematicArrive.h"

KinematicArrive::KinematicArrive(Mouse* character_, Vec3 target_, float radius_, float timeToTarget_)
{
    character = character_;
	target = target_;
	radius = radius_;
	timeToTarget = timeToTarget_;

}

KinematicArrive::~KinematicArrive()
{
	if (result) { delete result; }
}

KinematicSteeringOutPut KinematicArrive::GetSteering()
{
    result = new KinematicSteeringOutPut();

    // Get direction to the target, as a new vector
    result->velocity = target - character->GetPos();

    // check if we're within radius
    if (VMath::mag(result->velocity) < radius) {
        // request no steering
        result->velocity = Vec3(0, 0, 0);
        result->rotation = 0.0f;
        return *result;
    }

    // we need to move to our target, and we'd like
    // to get there in timeToTarget seconds.
    result->velocity = result->velocity / timeToTarget;

    // If this is too fast, clip it to max speed
    // kinematic body update() will do this


    result->rotation = 0;
    return *result;
}
