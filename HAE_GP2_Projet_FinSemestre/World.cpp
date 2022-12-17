#include "World.hpp"

void World::Update() {
	UpdateDeleted();
}

bool World::UpdateCollision(Vector2i pos) {
	if (pos.x > (Game::gameX / Game::cellSize) - 1 || pos.x < 0) {
		return true;
	}
	if (pos.y < 0 || pos.y >= (Game::gameY / Game::cellSize) - 1) {
		return true;
	}
	//foreach collider

	return false;
}

void World::UpdateDeleted() {
	
}
