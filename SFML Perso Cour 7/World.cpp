#include "World.hpp"

#include <SFML/Audio.hpp>
#include <iostream>

void World::Update() {
	
	//UpdateCollision();
	UpdateDeleted();
}

bool World::UpdateCollision(float cx, float cy) {
	if (cx > (Game::gameX / Game::cellSize) - 1 || cx < 0) {
		return true;
	}
	if (cy < 0 || cy >= (Game::gameY / Game::cellSize) - 1) {
		return true;
	}
	for (auto& w : walls) {
		if (w->cx == cx && w->cy == cy) {
			return true;
		}
	}

	return false;
}

void World::UpdateDeleted() {
	
}
