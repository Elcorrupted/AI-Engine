#ifndef AICHARACTER_H
#define AICHARACTER_H

#include "Body.h"
#include "SteeringOutput.h"

class AICharacter : public Body{
	friend ReadCharacterFile;
private:
	SteeringOutput* steering;
	int health;

public:
	AICharacter();
	AICharacter(Vec3 pos_, float orientation_);
	~AICharacter();

	void Update(float deltaTime, SteeringOutput* steering_);
	inline SteeringOutput* GiveSteeringOutput() { return steering; }
	inline int GetHealth() { return health; }
};
#endif
