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

	xr += dx;
	yr += dy;
	dx *= 0.9f; //friction
	dy *= 0.9f;

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

void Player::Update()
{
	currentState->UpdateState();

	float autoSpeed = 0.01;
	if (!path.empty()) {
		//SetCoordinateGtoW(Vector2f(path[0]->cx, path[0]->cy));
		//path.erase(path.begin());
		if (path[0]->cx > cx) {
			dx += autoSpeed;
		}
		else if (path[0]->cx < cx) {
			dx -= autoSpeed;
		}
		if (path[0]->cy > cy) {
			dy += autoSpeed;
		}
		else if (path[0]->cy < cy) {
			dy -= autoSpeed;
		}
		if (path[0]->cx == cx && path[0]->cy == cy) {
			path.erase(path.begin());
		}
	}

	xr += dx;
	yr += dy;
	dx *= 0.9f; //friction
	dy *= 0.9f;

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
		}
		else {
			yr++;
			cy--;
		}
	}

	Sync();
}
