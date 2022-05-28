#include "Cheese.h"
#include "VMath.h"

Cheese::Cheese() : Body() {}

Cheese::Cheese(Vec3 pos_, float orientation_)
{
	pos = pos_;
	orientation = orientation_;
}

Cheese::~Cheese()
{
}
