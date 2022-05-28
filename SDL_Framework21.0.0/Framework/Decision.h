#ifndef DECISION_H
#define DECISION_H

#include "Mouse.h"
#include "Trap.h"
#include "Scene2.h"
#include "SteeringBehaviour.h"
#include "VMath.h"
#include "Vector.h"
#include "DecisionTreeNode.h"

class Decision : public DecisionTreeNode {
public:
	Decision();
	~Decision();

	DecisionTreeNode* MakeDecision() override;
	virtual DecisionTreeNode* GetBranch() = 0; 

	void NearTrap(Vec3 pos1, Vec3 pos2, AICharacter* mouse, Trap* trap, SteeringBehaviour* aiSteering, const float deltaTime);
	void HealthCheck(AICharacter* mouse, Trap* trap, SteeringBehaviour* aiSteering, const float deltaTime);

protected:
	DecisionTreeNode* trueNode;
	DecisionTreeNode* falseNode;

	//Mouse* mouse;
	//Trap* trap;
	//class Scene2* scene2;
	//SteeringBehaviour* aiSteering;
	//const float deltaTime = 0.0f;
};

#endif // !DECISION_H
