#include "DynamicArrive.h"

DynamicArrive::DynamicArrive() : targetPos(Vec3()), timeToTarget(0.0f), targetRadius(0.0f), slowRadius(0.0f){
    character = nullptr;
}

DynamicArrive::DynamicArrive(AICharacter* character_, Vec3 pos_, float timeToTarget_, float targetRadius_, float slowRadius_)
{
    character = character_;
    targetPos = pos_;
    timeToTarget = timeToTarget_;
    targetRadius = targetRadius_;
    slowRadius = slowRadius_;
  
}

DynamicArrive::~DynamicArrive()
{
    if (character) delete character;
    if (result) { delete result; }
}

SteeringOutput* DynamicArrive::GetSteering()
{
    result = new SteeringOutput();
    
    //Get direction and distance to the target
    Vec3 direction = targetPos- character->GetPos();
    float distance = VMath::mag(direction);

    //Are we within the targetRadius
    float speedTowardTarget;
    if (distance < targetRadius) {
        return nullptr; //No output
    }

    //Checks to see if we have entered the slowdown radius around the target
    if (distance > slowRadius) {
         speedTowardTarget = character->GetComponent<PhysicsComponent>()->GetMaxSpeed(); //If not inside slowdown radius use max speed
    }
    //We have now entered the slowdown radius around the target
    else {
        speedTowardTarget = character->GetComponent<PhysicsComponent>()->GetMaxSpeed() * distance / slowRadius; // Slow down our character
    }

    //Combines the magnitude with direction to get velocity
    Vec3 velocityTowardTarget = direction;
    velocityTowardTarget = VMath::normalize(velocityTowardTarget);
    velocityTowardTarget *= speedTowardTarget;

    //Creates the desired change in linear motion
    result->linear = velocityTowardTarget - character->GetComponent<PhysicsComponent>()->GetVel();
    result->linear = result->linear / timeToTarget;

    //Make sure the change does not exceed the max acceleration of the character
    if (VMath::mag(result->linear) > character->GetComponent<PhysicsComponent>()->GetMaxAccel()) {
        result->linear = VMath::normalize(result->linear);
        result->linear *= character->GetComponent<PhysicsComponent>()->GetMaxAccel();
    }

    result->angular = 0.0f;
    return result;
}
