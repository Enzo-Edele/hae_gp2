#include <iostream>

#include "Entity.hpp"
#include "World.hpp"

Entity::Entity(Vector2f pos, Shape* shp) {
	cx = pos.x;
	cy = pos.y;

	sprite = shp;

	idleState = new Idle(this);
	coverState = new Cover(this);
	walkState = new Walking(this);
	jumpState = new Jumping(this);
	fallState = new Falling(this);

	currentState = idleState;
}

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
	currentState->UpdateState();

	dy += Game::gravity;

	xr += dx;
	yr += dy;
	dx *= 0.95f; //friction
	dy *= 0.95f;

	//activer gracité que quand nécessaire

	while (xr > 1) {
		if (HasCollision(cx + 1, cy)) {
			xr--;
			dx = 0;
		}
		else {
			xr--;
			cx++;
		}
	}
	while (xr < 0) {
		if (HasCollision(cx - 1, cy)) {
			xr++;
			dx = 0;
		}
		else {
			xr++;
			cx--;
		}
	}
	while (yr > 1) {
		if (HasCollision(cx, cy + 1)) {
			yr = 1.0f;
			dy = 0;
			enableGravity = false;
		}
		else {
			yr--;
			cy++;
		}
	}
	while (yr < 0) {
		if (HasCollision(cx, cy - 1)) {
			yr = 0.0f;
			dy = 0;
			enableGravity = false;
		}
		else {
			yr++;
			cy--;
		}
	}

	Sync();
}

void Entity::OnEvent(Event& event) {
	currentState->OnEvent(event);
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

void Entity::ChangeState(State* nstate) {
	currentState = nstate;
	currentState->ApplyState();
}
