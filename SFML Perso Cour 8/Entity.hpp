#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include<iostream>

#include "Game.hpp"

using namespace sf;

class Entity {
public:
	Shape* sprite;

	//Coordinate grid
	int cx = 0;
	int cy = 0;
	//Ratio grid in cell(offset)
	float xr = 0;
	float yr = 0;

	//final coordinate on screen
	float xx = 0;
	float yy = 0;

	//Direction manage movement
	float dx = 0;
	float dy = 0;

	bool enableGravity = true;

	//les passer en vector

	Entity(Vector2f pos, Shape* shp) {
		cx = pos.x;
		cy = pos.y;

		sprite = shp;
		
	}

	Entity() {

	}

	void SetCoordinateWtoG(Vector2f npos);

	void SetCoordinateGtoW(Vector2f npos);

	Vector2f GetCoordinateGrid(Vector2f grid);

	void Sync();

	void Update();

	bool HasCollision(float cx, float cy);

	void MoveGrid(Vector2f move);

	void MovePixel(Vector2f move);

	void Draw(RenderWindow& win) {
		win.draw(*sprite);
	}
};

class Wall : public Entity {
public:
	Wall(Vector2f posPx) : Entity(posPx, new RectangleShape(Vector2f(16, 16))) {
		SetCoordinateWtoG(posPx);

		sprite->setFillColor(Color::Red);

		sprite->setPosition(Vector2f(cx * Game::cellSize, cy * Game::cellSize));

		//td::cout << cx << " " << cy << "\n";
	}


};