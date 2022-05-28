#ifndef FLOATDECISION_H
#define FLOATDECISION_H

#include "Decision.h"

class FloatDecision : public Decision{
public:
	FloatDecision();
	~FloatDecision();

	//If the value used in the test value are between the min and max 
	//then true branch is used else false branch
	DecisionTreeNode* GetBranch();

	//Test behaviour will go into this function for inherited decisions
	virtual float TestValue() = 0;

protected:
	float minValue;
	float maxValue;

};
#pragma once
#endif // 
