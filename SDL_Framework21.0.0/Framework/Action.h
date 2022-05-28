#ifndef ACTION_H
#define ACTION_H

#include "DecisionTreeNode.h"

class Action :public DecisionTreeNode{
	DecisionTreeNode* MakeDecision() { return this; }
};
#endif // !ACTION_H

