#ifndef TILE_H
#define TILE_H

#include "Node.h"
#include "VMath.h"
#include "MMath.h"
#include <SDL.h>

using namespace MATH;

class Tile {
private:
	float width;
	float height;
	Vec3 position;
	Node node;

public:
	Tile(float width_, float height_, Vec3 position_, int label_, Vec3 nodePos);
	~Tile();

	void Render(SDL_Renderer *renderer_, Matrix4 projectionMatrix);
	inline Node GetNode() { return node; }
	inline Node* GetNodePntr() { return &node; }
};
#endif // !TILE_H

