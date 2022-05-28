#include "DecisionDistance.h"

DecisionDistance::DecisionDistance(const Vec3& pos1_, const Vec3& pos2_, float distance) {
	pos1 = pos1_;
	pos2 = pos2_;
	minValue = 0.0f;
	maxValue = distance;
}

DecisionDistance::~DecisionDistance(){}

float DecisionDistance::TestValue() {
	return VMath::distance(pos1, pos2);
}