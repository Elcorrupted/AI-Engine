#ifndef DYNAMICSEEK_H
#define DYNAMICSEEK_H

#include "Vector.h"
#include "VMath.h"
#include "Cheese.h"
#include "Mouse.h"
#include "SteeringBehaviour.h"

using namespace MATH;
class DynamicSeek: public SteeringBehaviour
{
protected:
		Vec3 target;
		//Mouse* character;
public:
	DynamicSeek(AICharacter* character_, Vec3 target_);
	~DynamicSeek();
	SteeringOutput* GetSteering();
};

#endif // !DYNAMICSEEK