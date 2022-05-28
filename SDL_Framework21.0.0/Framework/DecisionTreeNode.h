#ifndef DECISIONTREENODE_H
#define DECISIONTREENODE_H

class DecisionTreeNode {
public:
	virtual DecisionTreeNode* MakeDecision() = 0;
};

#endif // 
