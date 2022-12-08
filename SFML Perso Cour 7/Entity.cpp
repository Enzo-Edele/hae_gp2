#include <iostream>

#include "Entity.hpp"
#include "World.hpp"

//get pixel return grid
void Entity::SetCoordinateWtoG(Vector2f npos) {
	xx = npos.x;
	yy = npos.y;
	cx = (int)(xx / Game::cellSize);
	cy = (int)(yy / Game::cellSize);
	xr = (xx - cx * Game::cellSize) / Game::cellSize;
	yr = (yy - cy * Game::cellSize) / Game::cellSize;
}

//get gid return px
void Entity::SetCoordinateGtoW(Vector2f npos) {
	xx = (npos.x + xr) * Game::cellSize;
	yy = (npos.y + yr) * Game::cellSize;
	SetCoordinateWtoG(Vector2f(xx, yy));
}

void Entity::Sync()
{
	xx = (cx + xr) * Game::cellSize; //sync
	yy = (cy + yr) * Game::cellSize;
	sprite->setPosition(Vector2f(xx, yy));
}

void Entity::Update()
{
	bool needSync = true;

	xr += dx;
	yr += dy;
	dx *= 0.90f;
	dy *= 0.90f;

	//activer gracité que quand nécessaire
	yr += Game::gravity;

	xx = (cx + xr) * Game::cellSize; //sync
	yy = (cy + yr) * Game::cellSize; //sync



	while (xr > 1) {
		if (HasCollision(cx + 1, cy + yr)) {
			xr--;
			dx = 0;
		}
		else {
			if (HasCollision(cx + 1, cy)) {
				xr = 1.0;
				dx = 0;
			}
			else {
				xr--;
				cx++;
			}
		}
	}
	while (xr < 0) {
		if (HasCollision(cx - 1, cy + yr)) {
			xr++;
			dx = 0;
		}
		else {
			if (HasCollision(cx - 1, cy)) {
				xr = 0.0;
				dx = 0;
			}
			else {
				xr++;
				cx--;
			}
		}
	}
	while (yr > 1) {
		if (HasCollision(cx + xr, cy + 1)) {
			yr = 1.0f;
			dy = 0;
		}
		else {
			if (HasCollision(cx, cy + 1)) {
				yr = 1.0;
				dy = 0;
			}
			else
			{
				yr--;
				cy++;
			}
		}
	}
	while (yr < 0) {
		if (HasCollision(cx + xr, cy - 1)) {
			yr = 0.0f;
			dy = 0;
		}
		else {
			if (HasCollision(cx, cy - 1)) {
				yr = 0.0;
				dy = 0;
			}
			else {
				yr++;
				cy--;
			}
		}
	}
	Sync();
	//std::cout << "" << cx << " " << cy << "\n";
}

bool Entity::HasCollision(float cx, float cy)
{
	if (world.UpdateCollision(cx, cy))
		return true;

	return false;
}

void Entity::MoveGrid(Vector2f move)
{
	cx += move.x;
	cy += move.y;
}

void Entity::MovePixel(Vector2f move)
{
	dx += move.x;
	dy += move.y;
}
