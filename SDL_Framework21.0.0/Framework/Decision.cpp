#include "Decision.h"

Decision::Decision()
{
	//mouse = nullptr;
	//trap = nullptr;
	//scene2 = nullptr;
	//aiSteering = nullptr;
	//nearTrap = false;
}

Decision::~Decision()
{
}

DecisionTreeNode* Decision::MakeDecision() {
	return GetBranch()->MakeDecision();
}

void Decision::NearTrap(Vec3 pos1, Vec3 pos2, AICharacter* mouse, Trap* trap, SteeringBehaviour* aiSteering, const float deltaTime)
{
	//checks if the mouse is near the trap
	if (VMath::distance(pos1, pos2) <= 1.3)
	{
		printf("\ntrap!\n");
		trap->nearTrap = true;
	}
	//near trap is true
	if (trap->nearTrap == true)
	{
		// if yes checks health
		HealthCheck(mouse, trap, aiSteering, deltaTime);
	}
	//if no, the mouse continues on the path to the cheese
	else
	{
		mouse->Update(deltaTime, aiSteering->GetSteering());
	}
}

void Decision::HealthCheck(AICharacter* mouse, Trap* trap, SteeringBehaviour* aiSteering, const float deltaTime)
{
	int health = 2;
	//if health is not low mouse continues on the path and loses a life
	if (/*mouse->GetHealth()*/health == 2)
	{
		printf("\nHealth is: %d\n", /*mouse->GetHealth()*/health);
		mouse->Update(deltaTime, aiSteering->GetSteering());
		/*mouse->*/health--;
		printf("\nHealth after trap: %d\n", /*mouse->GetHealth()*/health);
		trap->nearTrap = false;
	}

	//if health is low mouse stops at the trap
	else if (/*mouse->GetHealth()*/health == 1)
	{
		printf("Mouse Stopped!\n");
	}
}
