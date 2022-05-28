#ifndef LOOKWHEREYOUREGOING_H
#define LOOKWHEREYOUREGOING_H

#include "Align.h"

class LookWhereYoureGoing : public Align{
public:
	LookWhereYoureGoing(AICharacter* character_);
	~LookWhereYoureGoing();

	SteeringOutput* GetSteering();

private:
	Vec3 targetPos;
};

#endif // LOOKWHEREYOUREGOING_H
