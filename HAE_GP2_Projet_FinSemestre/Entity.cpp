#include "Entity.hpp"

Entity::Entity(Vector2i pos, Shape* shp) {
	posGrid = pos;

	shape = shp;
}

void Entity::SetCoordinateWtoG(Vector2f npos) {
	posWorld = npos;
	posGrid.x = (int)(posWorld.x / Game::cellSize);
	posGrid.y = (int)(posWorld.y / Game::cellSize);
	gridOffset.x = (posWorld.x - posGrid.x * Game::cellSize) / Game::cellSize;
	gridOffset.y = (posWorld.y - posGrid.y * Game::cellSize) / Game::cellSize;
}

void Entity::SetCoordinateGtoW(Vector2i npos) {
	posWorld.x = (npos.x + gridOffset.x) * Game::cellSize;
	posWorld.y = (npos.y + gridOffset.y) * Game::cellSize;
	SetCoordinateWtoG(posWorld);
}

bool Entity::HasCollision(Vector2i pos)
{
	if (world.UpdateCollision(pos)) {
		return true;
	}

	return false;
}

void Entity::Update() {

}
