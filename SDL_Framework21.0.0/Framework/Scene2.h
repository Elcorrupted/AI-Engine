#ifndef SCENE2_H
#define SCENE2_H

#include "MMath.h"
#include "VMath.h"
#include "Scene.h"

#include "AICharacter.h"
#include "Cheese.h"
#include "Mouse.h"
#include "Trap.h"

#include "BlendedSteering.h"
#include "KinematicSeek.h"
#include "KinematicArrive.h"
#include "LookWhereYoureGoing.h"
#include "DynamicSeek.h"
#include "DynamicArrive.h"
#include "SteeringOutput.h"
#include "FollowPath.h"

#include "Tile.h"
#include "Graph.h"
#include "Decision.h"

#include <SDL.h>
#include <vector>

using namespace MATH;

class Scene2 : public Scene {
public:
	Scene2(SDL_Window* sdlWindow_, SDL_Renderer* renderer_);
	~Scene2();
	bool OnCreate();
	void OnDestroy();
	void Update(const float deltaTime);
	void Render();

	Cheese* cheese;
	AICharacter* mouse;
	Trap* trap;
	class Decision* decision;
	Vec3 getMousePosition();
	BlendedSteering* aiSteering;

	//Node trapNode = sceneGraph->FindNode(trap->getPos());
	//Node trapNode;

	SDL_Surface* cheeseImage;
	SDL_Surface* mouseImage;
	SDL_Surface* trapImage;
private:
	float screenWidth;
	float screenHeight;
	float tileSize;

	std::vector<SDL_Texture*> texturelist;
	SDL_Renderer* renderer;
	Graph* sceneGraph;
	SDL_Window* window;
	Matrix4 projectionMatrix;
	std::vector<Tile*> tileList;
	std::vector<Body*> objectlist;
};
#endif // !SCENE2_H

