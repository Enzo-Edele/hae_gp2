#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Game.hpp"

using namespace sf;

class Entity {
public:
	Shape* sprite;

	//grid coordinat
	int cx = 0;
	int cy = 0;
	//grid ratio within the cell (offset)
	float xr = 0;
	float yr = 0;

	//final coordinate on screen
	float xx = 0;
	float yy = 0;

	float dx = 0;
	float dy = 0;

	Entity(Vector2f pos, Shape* shp) {
		cx = pos.x;
		cy = pos.y;

		sprite = shp;
		//sprite->setOrigin(Vector2f(8, 8));
	}

	void SetCoordinateWtoG(Vector2f npos) {
		xx = npos.x;
		yy = npos.y;
		cx = (int)(xx / Game::cellSize);
		cy = (int)(yy / Game::cellSize);
		xr = (xx - cx * Game::cellSize) / Game::cellSize;
		yr = (yy - cy * Game::cellSize) / Game::cellSize;
	}

	void SetCoordinateGtoW(Vector2f npos) {
		xx = (npos.x + xr) * Game::cellSize;
		yy = (npos.y + yr) * Game::cellSize;
		SetCoordinateWtoG(Vector2f(xx, yy));
	}

	void Sync() {

	}

	void Update();

	bool HasCollision();

	void MoveGrid(Vector2f move);

	void MovePixel(Vector2f move);

	void Draw(RenderWindow& win) {
		win.draw(*sprite);
	}
};