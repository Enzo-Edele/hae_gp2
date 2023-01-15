#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include<iostream>

#include "Game.hpp"

class Entity {
public:
	Shape* shape = nullptr;
	Texture texture;
	Sprite sprite;

	Vector2i posGrid = Vector2i(0, 0);
	Vector2f gridOffset = Vector2f(0, 0);
	Vector2f posWorld = Vector2f(0, 0);
	Vector2f size = Vector2f(0, 0);

	Vector2f direction = Vector2f(0, 0);

	Vector2i offsetShoot = Vector2i(0, 0); //faire une liste au besoin et add index en int

	Entity(Vector2i pos, Vector2f shapeSize, Shape* shp);

	auto GetLocalBounds() const {
		return shape->getLocalBounds();
	}

	auto GetGlobalBounds() const {
		return shape->getGlobalBounds();
	}

	void SetCoordinateWtoG(Vector2f npos);

	void SetCoordinateGtoW(Vector2i npos);

	bool HasCollision(Vector2i pos);

	void Update();

	void Move(Vector2f movDirection);

	void Draw(RenderWindow& win) {
		win.draw(*shape);
		win.draw(sprite);
	}
};

class Cell : public Entity {
public:
	Cell(Vector2i pos, Vector2f size, Shape* shp, Color color);

	void Draw(RenderWindow& win) {
		win.draw(*shape);
	}
};

class Blocker : public Entity {
public:
	Blocker(Vector2i pos, Vector2f size, Shape* shp);

	void Draw(RenderWindow& win) {
		win.draw(*shape);
	}
};

//EntityTexture

class Player : public Entity {
public:
	Texture projectile;

	Player(Vector2i pos, Vector2f size, Shape* shp, Texture newTexture);

	//hasCollision

	void Update();

	void Draw(RenderWindow& win) {
		//win.draw(*shape);
		win.draw(sprite);
	};

	void Shoot();

	void Killed();
};

class Eneny : public Entity {
public:
	Vector2i startPos;
	//liste de commande

	Eneny(Vector2i pos, Vector2f size, Shape* shp, Texture newTexture);

	//hasCollision
	bool HasCollision(Vector2i pos);

	void Update();

	void Draw(RenderWindow& win) {
		//win.draw(*shape);
		win.draw(sprite);
	};

	void Shoot();
};

class Projectile : public Entity {
public:
	Projectile(Vector2i pos, Vector2f size, Vector2f offset, Shape* shp, Texture newTexture);

	//hasCollision ???
	bool HasCollision(Vector2i pos);

	void Draw(RenderWindow& win) {
		win.draw(*shape);
		win.draw(sprite);
	};

	void Update();
};