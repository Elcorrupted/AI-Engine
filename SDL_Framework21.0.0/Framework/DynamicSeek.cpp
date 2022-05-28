#include "DynamicSeek.h"

DynamicSeek::DynamicSeek(AICharacter* character_, Vec3 target_)
{
    character = character_;
    target = target_;
}

DynamicSeek::~DynamicSeek()
{
    
}

SteeringOutput* DynamicSeek::GetSteering()
{
    result = new SteeringOutput();

    // Get direction to the target, as a new vector
    result->linear = target - character->GetPos();

    // acceleration is along this direction, at full value
    result->linear = VMath::normalize(result->linear);
    result->linear = character->GetComponent<PhysicsComponent>()->GetMaxAccel() * result->linear;

    result->angular = 0;
    return result;
}
