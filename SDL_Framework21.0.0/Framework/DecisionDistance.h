#ifndef DECISIONDISTANCE_H
#define DECISIONDISTANCE_H

#include "FloatDecision.h"

class DecisionDistance : public FloatDecision {
public:
	DecisionDistance(const Vec3& pos1_, const Vec3& pos2_, float distance);
	~DecisionDistance();

	float TestValue() override;

private:
	Vec3 pos1, pos2;
	float testValue;
};

#endif
