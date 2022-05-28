#include "Trap.h"
#include "VMath.h"

Trap::Trap(): Body(), nearTrap(false){}

Trap::Trap(Vec3 pos_, float orientation_)
{
	pos = pos_;
	orientation = orientation_;
	nearTrap = false;
}

Trap::~Trap()
{
}
