#pragma once

#include "SFML/Graphics/Shape.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

using namespace sf;

class Entity {
public:
	Shape* sprite = nullptr; // pour le rendu
	//FloatRect localBox;//pour les collisions

	Entity(Vector2f pos, Shape* shp);

	auto getLocalBounds() const {
		return sprite->getLocalBounds();
	}

	auto getGlobalBounds() const {
		return sprite->getGlobalBounds();
	}

	auto getPosition() {
		return sprite->getPosition();
	}

	auto setPosition(const Vector2f& v) {
		sprite->setPosition(v);
	}

	void Draw(RenderWindow& win) {
		win.draw(*sprite);
	}

	virtual void Hit() {

	}
};

class Pad : public Entity {
public :
	//pour appeler construct parend on lui passe en valeur les arg de l'enfant puis on peut ajouter dans l'enfant
	Pad(Vector2f padPos);

	int bonus = 0;
	float speed = 9.0f;
	//max & min speed
	//max et min size
	void MoveRight();
	void MoveLeft();

	void Hit(int type);
};

//class ball
class Ball : public Entity{
public:
	Vector2f speed;
	Vector2f lastPos;

	Pad* hooked = nullptr;
	int xOffset = 0;
	int yOffset = 0;

	Ball(Pad* pad);

	void initPos(Pad* pad);

	void Update();
};

class Wall : public Entity{ 
public:
	Wall(FloatRect r);
};

class Brick : public Entity { 
public:
	int hitPoint = 1;

	Brick(sf::FloatRect r, Color c = Color::White);
	virtual void Hit() override;
};

class Bonus : public Entity {
public: 
	Vector2f speed;
	int type;

	Bonus(Vector2f pos);

	void Update();
};
