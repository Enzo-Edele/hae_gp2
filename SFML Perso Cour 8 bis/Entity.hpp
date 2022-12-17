#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include<iostream>

#include "Game.hpp"
#include "State.hpp"

using namespace sf;

class State;

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
	//les passer en vector

	bool enableGravity = true;

	enum class StateEnum
	{
		Idle,
		Walking,
		Jumping,
		Falling
	};

	StateEnum state = StateEnum::Idle;

	State* currentState = nullptr;
	State* idleState = nullptr;
	State* coverState = nullptr;
	State* walkState = nullptr;
	State* jumpState = nullptr;
	State* fallState = nullptr;

	Entity(Vector2f pos, Shape* shp);

	Entity() {

	}

	void SetCoordinateWtoG(Vector2f npos);

	void SetCoordinateGtoW(Vector2f npos);

	void Sync();

	void Update();

	void OnEvent(Event& event);

	bool HasCollision(float cx, float cy);

	void MoveGrid(Vector2f move);

	void MovePixel(Vector2f move);

	void Draw(RenderWindow& win) {
		win.draw(*sprite);
	}

	void ChangeState(State* nstate);
};

class Wall : public Entity {
public:
	Wall(Vector2f posPx) : Entity(posPx, new RectangleShape(Vector2f(16, 16))) {
		SetCoordinateWtoG(posPx);

		//sprite->setOrigin(Vector2f(16, 16)); //l'offset influe sur les collisions

		sprite->setFillColor(Color::Red);

		sprite->setPosition(Vector2f(cx * Game::cellSize, cy * Game::cellSize));

		//td::cout << cx << " " << cy << "\n";
	}


};

class Cell : public Entity {
public:
	int weight = 0;

	Cell(Vector2f pos, Color color = Color::Cyan) : Entity(pos, new CircleShape(2)) {
		SetCoordinateGtoW(pos);

		sprite->setFillColor(color);

		sprite->setPosition(Vector2f(cx * Game::cellSize + 8, cy * Game::cellSize + 8));
		
		weight = 0;
	}
};

class Player : public Entity {
public:
	std::vector<Cell*> path;

	Player(Vector2f pos) : Entity(pos, new RectangleShape(Vector2f(16, 16))) {
		//sprite->setOrigin(Vector2f(16, 16)); //l'offset t'entraine des pb de collision
	}

	void Update();
};