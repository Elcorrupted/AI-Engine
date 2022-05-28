#include "KinematicSeek.h"

KinematicSeek::KinematicSeek(Mouse* character_, Vec3 target_)
{
    character = character_;
    target = target_;
}

KinematicSeek::~KinematicSeek()
{
    if (result) { delete result; }
}

KinematicSteeringOutPut KinematicSeek::getSteering()
{
    result = new KinematicSteeringOutPut();

    // Get direction to the target, as a new vector
    result->velocity = target - character->GetPos();

    // velocity is along this direction, at full speed
    result->velocity = VMath::normalize(result->velocity);
    result->velocity *= character->GetMaxSpeed();

    result->rotation = 0;
    return *result;
}
