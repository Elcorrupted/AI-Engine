#include "Body.h"

Body::Body() : pos(0.0f, 0.0f, 0.0f), orientation(0.0f), components(std::vector<Component*>()) {
	
}

Body::Body(Vec3 pos_, float orientation_) : components(std::vector<Component*>()) {
	pos = pos_;
	orientation = orientation_;
}

Body::~Body(){}