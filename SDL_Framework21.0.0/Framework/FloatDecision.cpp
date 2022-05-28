#include "FloatDecision.h"

FloatDecision::FloatDecision() : minValue(FLT_MIN), maxValue(FLT_MAX) {
}

FloatDecision::~FloatDecision(){}

DecisionTreeNode* FloatDecision::GetBranch() {
	if (maxValue >= TestValue() >= minValue) {
		return trueNode;
	}
	else {
		return falseNode;
	}
}