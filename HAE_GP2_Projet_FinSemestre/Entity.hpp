#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include<iostream>

#include "Game.hpp"

enum class EnemyType : int {
	cruiser,
	corvette,
	missileCorvette,
};

enum class ProjectileType : int {
	laser,
	missile,
};

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
	float lifespawn = 0.0f;
	Texture boom0;
	Texture boom1;
	Texture boom2;
	Texture boom3;

	Cell(Vector2i pos, Vector2f size, Shape* shp, Color color);

	void Lifespawn(float dt);

	void Draw(RenderWindow& win) {
		//win.draw(*shape);
		win.draw(sprite);
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

class Player : public Entity{
public:
	Texture projectile;

	float invincibleTimer;
	float shotTimer;

	Player(Vector2i pos, Vector2f size, Shape* shp, Texture newTexture);

	//hasCollision

	void Update(float dt);

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
	Texture projectile;
	Texture missile;
	//liste de commande
	std::vector<Vector2f> shootDirections;
	float shotTimer;

	EnemyType type;

	Eneny(Vector2i pos, Vector2f size, Shape* shp, Texture newTexture, EnemyType nType);

	//hasCollision
	bool HasCollision(Vector2i pos);

	void Update(float dt);

	void Draw(RenderWindow& win) {
		//win.draw(*shape);
		win.draw(sprite);
	};

	void Shoot();

	void ShootSpe();
};

class Projectile : public Entity {
public:
	Projectile(Vector2i pos, Vector2f size, Vector2f offset, Shape* shp, Texture newTexture, Vector2f dir, ProjectileType nType);

	Transform trs;
	ProjectileType type;

	//hasCollision ???
	bool HasCollision(Vector2i pos);

	void Draw(RenderWindow& win) {
		win.draw(*shape);
		win.draw(sprite);
	};

	void Forward(int px);

	void Update();
};