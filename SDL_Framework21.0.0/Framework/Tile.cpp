#include "Tile.h"

Tile::Tile(float width_, float height_, Vec3 position_, int label_, Vec3 nodePos) {
	width = width_;
	height = height_;
	position = position_;	
	node = Node(label_, nodePos);
}

Tile::~Tile(){}

void Tile::Render(SDL_Renderer *renderer_, Matrix4 projectionMatrix){
	Vec3 screenCoords = projectionMatrix * position;

	SDL_Rect tile;
	tile.x = static_cast<int>(screenCoords.x);
	tile.y = static_cast<int>(screenCoords.y);
	tile.w = static_cast<int>(width);
	tile.h = static_cast<int>(height);

	if (!node.GetWall()) {	
		SDL_SetRenderDrawColor(renderer_, 0, 0, 255, 1);
		SDL_RenderDrawRect(renderer_, &tile);	
	}
	else {
		SDL_SetRenderDrawColor(renderer_, 100, 100, 100, 1);
		SDL_RenderFillRect(renderer_, &tile);			
	}
}