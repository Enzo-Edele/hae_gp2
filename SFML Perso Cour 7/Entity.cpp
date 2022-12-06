#include <iostream>

#include "Entity.hpp"

void Entity::Update()
{
	bool needSync = false;

	xr += dx;
	yr += dy;
	dx = 0;
	dy = 0;

	xx = (cx + xr) * Game::cellSize;
	yy = (cy + yr) * Game::cellSize;

	while (xr > 1) {
		xr--;
		cx++;
		//collide
	}
	while (xr < 0) {
		xr++;
		cx--;
	}
	while (yr > 1) {
		yr--;
		cy++;
	}
	while (yr < 0) {
		yr++;
		cy--;
	}

	sprite->setPosition(Vector2f(xx, yy));
	std::cout << "" << cx << " " << cy << "\n";
}

bool Entity::HasCollision()
{
	return false;
}

void Entity::MoveGrid(Vector2f move)
{
	cx += move.x;
	cy += move.y;
}

void Entity::MovePixel(Vector2f move)
{
	dx = move.x;
	dy = move.y;
}
