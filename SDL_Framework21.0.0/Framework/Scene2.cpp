#include "Scene2.h"
#include "ReadCharacterFile.h"

#include <SDL.h>
#include <SDL_image.h>
Scene2::Scene2(SDL_Window* sdlWindow_, SDL_Renderer* renderer_) :cheese(nullptr), mouse(nullptr), trap(nullptr),
										cheeseImage(nullptr), mouseImage(nullptr), trapImage(nullptr),
										sceneGraph(nullptr), aiSteering(nullptr), decision(nullptr)
{
	renderer = renderer_;
	texturelist.reserve(10);
	window = sdlWindow_;
}

Scene2::~Scene2()
{
	OnDestroy();
}

bool Scene2::OnCreate()
{
	int w, h;
	//Graphics
	{
	SDL_GetWindowSize(window, &w, &h);

	//add textures
	texturelist.push_back(IMG_LoadTexture(renderer, "textures/mouse.png"));
	texturelist.push_back(IMG_LoadTexture(renderer, "textures/cheese.png"));
	texturelist.push_back(IMG_LoadTexture(renderer, "textures/mouse_trap.png"));
	}

	//Declaration of what each tile square size is 
	//and the screen's width and height in units.
	tileSize = 100.0f;
	screenWidth = 30.0f;
	screenHeight = 15.0f;

	//Screen pixel size is 1080 by 720. The screen unit size is 30 by 15
	//These ratios are what each pixel is worth per unit 
	//The tileSize is in pixels and the position is in screen units. The ratios are used for conversions
	float widthRatio = screenWidth / w;
	float heightRatio = screenHeight / h;

		//Used for assigning node label and will hold total number of nodes
	int numberOfNodes = 0;
		//For number of rows/number of nodes in a column
	int nodesInColumn = 0;

	//Creation of the tiles in the tileList vector
	for (float positionY = screenHeight;  positionY > 0.0f; positionY -= tileSize * heightRatio) {
		for (float positionX = 0.0f; positionX < screenWidth; positionX += tileSize * widthRatio) {
			//Adds tile pointers to the tileList
			tileList.push_back(new Tile(tileSize, tileSize, Vec3(positionX, positionY, 1.0f), //Tile info
				numberOfNodes, Vec3(positionX + (tileSize * 0.5f * widthRatio), positionY - (tileSize * 0.5f * heightRatio), 0.0f))); //Node info
			numberOfNodes++;
		}
		//Number of rows or number of nodes in a column
		nodesInColumn++;
	}

	//Creates a graph using the what was created above
	sceneGraph = new Graph(numberOfNodes, nodesInColumn, tileList);
	//Adds a "wall" to the left and under the goal(cheese), goal is closest to node 32 with current settings
	sceneGraph->RemoveConnection(tileList[31]->GetNodePntr());
	sceneGraph->RemoveConnection(tileList[45]->GetNodePntr());

	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, screenWidth, 0.0f, screenHeight, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;

	//Working stuff
 	{
 	//Initial linear simulated physics data used in creation of physics component
 	LinearMotion linear;
 	linear.vel = Vec3();
 	linear.accel = Vec3();
 	linear.maxSpeed = 13.0f;
 	linear.maxAccel = 1.0f;
 
 	//Initial angular simulated physics data used in creation of physics component
 	AngularMotion angular;
 	angular.rotation = 0.0f;
 	angular.maxRotation = M_PI / 2;
 
 
 	//Could create other constructors to allow less data to be needed up front, since most are normally going to start at 0
 	//Add pos, orientation to the mouse
 	mouse = new AICharacter(Vec3(1.0f, 6.7f, 0.0f), -M_PI / 2);
 	//Add component to mouse. Add vel, accel, maxspeed, maxaccel, rotation, maxRot, mass, and a pointer to the mouses steering output, which changes every update call
 	mouse->AddComponent<PhysicsComponent>(linear, angular, 100.0f, mouse->GiveSteeringOutput());
 
 	cheese = new Cheese(Vec3(tileList[32]->GetNode().GetPos()), 0.0f);
 	trap = new Trap(Vec3(tileList[41]->GetNode().GetPos()), 0.0f);
 	}

	//Not working
	/*
	if (ReadCharacterFile::ReadXML<AICharacter>("CharacterFile.xml", mouse)) {
		printf("Mouse could not be loaded from text file");
	}
	if (ReadCharacterFile::ReadXML<Cheese>("CharacterFile.xml", cheese)) {
		printf("Cheese could not be loaded from text file");
	}
	if (ReadCharacterFile::ReadXML<Trap>("CharacterFile.xml", trap)) {
		printf("Trap could not be loaded from text file");
	}*/
// 	*mouse = ReadCharacterFile::ReadXML<AICharacter>("CharacterFile.xml");
// 	*cheese = ReadCharacterFile::ReadXML<Cheese>("CharacterFile.xml");
// 	*trap = ReadCharacterFile::ReadXML<Trap>("CharacterFile.xml");

	//Finds the node closest to the AI character and the goal for use in steering
	Node mouseNode = sceneGraph->FindNode(mouse->GetPos());
	Node cheeseNode = sceneGraph->FindNode(cheese->GetPos());
	//Node trapNode = sceneGraph->FindNode(trap->getPos());
	
	//Probably should be held elsewhere
	const float timeToTarget = 0.1f;
	float targetRadius = 0.1f;
	float slowRadius = 10.0f;

	//BlendedSteering which will create an SteeringOutput for the mouse based on the behaviours added to it's list
	aiSteering = new BlendedSteering(mouse);
	//Adds the FollowPath behaviour to the blended steering list that uses the A* algorithms output path
	aiSteering->AddBehaviour(new FollowPath(mouse, timeToTarget, targetRadius, slowRadius, sceneGraph->A_StarPath(mouseNode, cheeseNode)), 1.0f);
	//Adds the LookWhereYoureGoing behaviour to the blended steering list
	aiSteering->AddBehaviour(new LookWhereYoureGoing(mouse), 1.0f);
	//aiSteering = new FollowPath(mouse, timeToTarget, targetRadius, slowRadius, sceneGraph->A_StarPath(mouseNode, trapNode));

	/*if (mouseNode.GetPos().y == trapNode.GetPos().y)
	{
		printf("trap reached\n");
	}*/

	return true;
}

void Scene2::OnDestroy()
{
	delete mouse, mouseImage, cheese, cheeseImage, trap, trapImage;
	if (window) SDL_DestroyWindow(window);
	if (sceneGraph) delete sceneGraph;
	if (aiSteering) delete aiSteering;
	for (Tile* inList : tileList) {
		if (inList) delete inList;
	}
	if (renderer) renderer = nullptr;
	for (auto t : texturelist) {
		if (t) SDL_DestroyTexture(t);
	}
}

void Scene2::Update(const float deltaTime)
{
	decision->NearTrap(mouse->GetPos(), trap->GetPos(), mouse, trap, aiSteering, deltaTime);
}

void Scene2::Render()
{
	if (renderer) {
		SDL_RenderClear(renderer);
	}

	//Adjust here to offset the images
	Vec3 screenCoords1 = projectionMatrix * mouse->GetPos();
	Vec3 screenCoords2 = projectionMatrix * cheese->GetPos();
	Vec3 screenCoords3 = projectionMatrix * trap->GetPos();

	SDL_Rect s1,s2, s3;

	SDL_QueryTexture(texturelist[0], nullptr, nullptr, &s1.w, &s1.h);
	SDL_QueryTexture(texturelist[1], nullptr, nullptr, &s2.w, &s2.h);
	SDL_QueryTexture(texturelist[2], nullptr, nullptr, &s3.w, &s3.h);
	s1.w /= 12;
	s1.h /= 12;
	s2.w /= 30;
	s2.h /= 30;
	s3.w /= 10;
	s3.h /= 10;

	s1.x = static_cast<int>(screenCoords1.x) - s1.w / 2;
	s1.y = static_cast<int>(screenCoords1.y) - s1.h / 2;
	s2.x = static_cast<int>(screenCoords2.x) - s2.w / 2;
	s2.y = static_cast<int>(screenCoords2.y) - s2.w / 2;
	s3.x = static_cast<int>(screenCoords3.x) - s3.w / 2;
	s3.y = static_cast<int>(screenCoords3.y) - s3.w / 2;

	//Rendering the tiles
	for (auto tile : tileList) {
		tile->Render(renderer, projectionMatrix);
	}
	
	float toDegrees = 180.0f / M_PI;
	SDL_RenderCopyEx(renderer, texturelist[1], nullptr, &s2, cheese->GetOrientation() * toDegrees, nullptr, SDL_FLIP_NONE);
	SDL_RenderCopyEx(renderer, texturelist[2], nullptr, &s3, trap->GetOrientation() * toDegrees, nullptr, SDL_FLIP_NONE);
	SDL_RenderCopyEx(renderer, texturelist[0], nullptr, &s1, mouse->GetOrientation() * toDegrees, nullptr, SDL_FLIP_NONE);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderPresent(renderer);
}

Vec3 Scene2::getMousePosition()
{// copied here for debugging, see Scene2::OnCreate();
	float xAxis = 30.0f;
	float yAxis = 15.0f;

	int w, h;		// window width and height
	int x, y;		// mouse position in screen coords

	// convert mouse's screen coords to world coords
	SDL_GetWindowSize(window, &w, &h);
	Uint32 buttons;
	buttons = SDL_GetMouseState(&x, &y);
	// Bottom left corner will be [0,0]
	y = h - y;

	Vec3 worldCoordsFromScreenCoords;
	worldCoordsFromScreenCoords.x = xAxis / static_cast<float>(w) * static_cast<float>(x);
	worldCoordsFromScreenCoords.y = yAxis / static_cast<float>(h) * static_cast<float>(y);
	worldCoordsFromScreenCoords.z = 0.0f;

	if (DEBUG) {
		std::cout << worldCoordsFromScreenCoords.x<<"  "<<worldCoordsFromScreenCoords.y << std::endl;
		if ((buttons & SDL_BUTTON_LMASK) != 0) {
			SDL_Log("Mouse Button 1 (left) is pressed.");
		}
	}
	
	return worldCoordsFromScreenCoords;
}
