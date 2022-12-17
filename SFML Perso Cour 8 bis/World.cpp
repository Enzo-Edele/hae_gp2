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

void World::DrawValidCell(Vector2i bound) {
	validCells.clear();
	for (int y = 0; y < bound.y; y++) {
		for (int x = 0; x < bound.x; x++) {
			if (UpdateCollision(x, y)) {
				int here = 0;
			}
			else {
				validCells.push_back(new Cell(Vector2f(x, y)));
			}
		}
	}
}

void World::DrawAllPath(Vector2i size)
{
	
}

void World::DrawPath(std::vector<Cell*> path)
{
	//validCells.clear();
	//pathCells.clear();
	for (auto& p : path) {
		p->sprite->setFillColor(Color::Red);
		pathCells.push_back(p);
	}
}
