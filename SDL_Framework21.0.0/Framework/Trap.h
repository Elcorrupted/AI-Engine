#ifndef TRAP_H
#define TRAP_H

#include "Body.h"
#include"SteeringOutput.h"
#include <SDL.h>


//A non AI character
class Trap : public Body
{
public:
	Trap();
	Trap(Vec3 pos_,	float orientation_);
	~Trap();

	bool nearTrap;
};

#endif // !TRAP_H

