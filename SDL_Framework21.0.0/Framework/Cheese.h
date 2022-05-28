#ifndef CHEESE_H
#define CHEESE_H

#include "Body.h"
#include"SteeringOutput.h"
#include <SDL.h>


//A non AI character
class Cheese: public Body
{
public:
	Cheese();
	Cheese(Vec3 pos_, float orientation_);
	~Cheese();
};

#endif // !CHEESE_H