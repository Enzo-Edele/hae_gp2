#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include<iostream>

#include "Game.hpp"
#include "World.hpp"

class Entity {
public:
	Shape* shape = nullptr;

	Vector2i posGrid;
	Vector2f gridOffset;
	Vector2f posWorld;

	Vector2f direction;

	Vector2f offsetShoot; //faire une liste au besoin et add index en int

	Entity(Vector2i pos, Shape* shp);

	void SetCoordinateWtoG(Vector2f npos);

	void SetCoordinateGtoW(Vector2i npos);

	bool HasCollision(Vector2i pos);

	void Update();
};

class Player : public Entity{
public:
	Player(Vector2i pos, Shape* shp) : Entity(pos, shp){

	}
};

class Eneny : public Entity {
public:
	Eneny(Vector2i pos, Shape* shp) : Entity(pos, shp) {

	}
};