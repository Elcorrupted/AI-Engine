#ifndef STEERINGOUTPUT_H
#define STEERINGOUTPUT_H

#include "Vector.h"
using namespace MATH;

class SteeringOutput
{
public:
	Vec3 linear;
	float angular;

	SteeringOutput();
	~SteeringOutput();
	SteeringOutput(Vec3 linear_, float angular_);

	//Allows addition of SteerintOutputs
	inline const SteeringOutput operator +(const SteeringOutput& v) const {
		return SteeringOutput(linear + v.linear, angular + v.angular);
	}
	//+= overload for SteeringOutput
	inline SteeringOutput& operator +=(const SteeringOutput& v) {
		linear += v.linear;
		angular += v.angular;
		return *this;
	}
	//Allows multiplication of SteeringOutput by a float
	inline SteeringOutput& operator *(const float& v) {
		SteeringOutput temp;
		temp.linear = linear * v;
		temp.angular = angular * v;
		return temp;
	}
};

#endif // !STEERINGOUT_H