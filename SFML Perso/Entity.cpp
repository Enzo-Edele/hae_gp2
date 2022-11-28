#include "Entity.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/CircleShape.hpp"
#include <iostream>

#include "Lib.hpp"
#include "World.hpp"
#include "Game.hpp"
#include "Particles.hpp"

Entity::Entity(Vector2f pos, Shape* shp) {
	this->sprite = shp;
	sprite->setPosition(pos);
}

//pour appeler construct parend on lui passe en valeur les arg de l'enfant puis on peut ajouter dans l'enfant

Pad::Pad(Vector2f padPos) : Entity(padPos, new RectangleShape(Vector2f(Game::padX, Game::padY))) {
	auto rect = (sf::RectangleShape*)sprite;
	auto bnd = rect->getLocalBounds();
	rect->setOrigin(Vector2f(bnd.width * 0.5, bnd.height * 0.5f));
	rect->setFillColor(Color::Red);
	rect->setOutlineColor(Color::Yellow);
	rect->setOutlineThickness(2);
}

void Pad::MoveRight() {
	sprite->setPosition(sprite->getPosition() + Vector2f(speed, 0));
	Vector2f pos = sprite->getPosition();
	if (pos.x > 1280 - getLocalBounds().width * 0.5) {
		sprite->setPosition(Vector2f(1280 - getLocalBounds().width * 0.5, Game::groundHeight));
	}
}

void Pad::MoveLeft() {
	sprite->setPosition(sprite->getPosition() + Vector2f(-speed, 0));
	Vector2f pos = sprite->getPosition();
	if (pos.x < 0 + getLocalBounds().width * 0.5) {
		sprite->setPosition(Vector2f(0 + getLocalBounds().width * 0.5, Game::groundHeight));
	}
}

void Pad::Hit(int type)
{
	Vector2f pos = getPosition();

	if (type == 0 && bonus < 2) {
		sprite = new RectangleShape(Vector2f(getLocalBounds().width - Game::padX * 0.25, 24));
		auto rect = (sf::RectangleShape*)sprite;
		auto bnd = rect->getLocalBounds();
		rect->setOrigin(Vector2f(bnd.width * 0.5, bnd.height * 0.5f));
		rect->setFillColor(Color::Red);
		rect->setOutlineColor(Color::Yellow);
		rect->setOutlineThickness(2);
		rect->setPosition(pos);
		bonus++;
	}
	if (type == 1 && bonus > -2) {
		sprite = new RectangleShape(Vector2f(getLocalBounds().width + Game::padX * 0.25, 24));
		auto rect = (sf::RectangleShape*)sprite;
		auto bnd = rect->getLocalBounds();
		rect->setOrigin(Vector2f(bnd.width * 0.5, bnd.height * 0.5f));
		rect->setFillColor(Color::Red);
		rect->setOutlineColor(Color::Yellow);
		rect->setOutlineThickness(2);
		rect->setPosition(pos);
		bonus--;
	}
}

Ball::Ball(Pad* pad) : Entity(Vector2f(), new CircleShape(12)) {
	auto circ = (RectangleShape*)sprite;
	circ->setOrigin(12, 12);
	initPos(pad);

	circ->setFillColor(sf::Color::Blue);
	circ->setOutlineColor(sf::Color::Cyan);
	circ->setOutlineThickness(2);
}

void Ball::initPos(Pad* pad) {
	auto p = hooked = pad;
	if (pad) {
		xOffset = p->getLocalBounds().width * 0.1f;
		yOffset = -p->getLocalBounds().height * 1.0f;
		speed = Vector2f(0, 0);
	}
}

int fr = 0;
void Ball::Update() {
	lastPos = sprite->getPosition();

	if (hooked) {
		sprite->setPosition(hooked->getPosition() + Vector2f(xOffset, yOffset));
	}
	else {
		sprite->setPosition(sprite->getPosition() + speed);
	}

	if ((fr > 2) && !hooked) {
		particle.addBall(sprite->getPosition(), Vector2f(4, 4), Color::Red);
		fr = 0;
	}
	fr++;
}

Wall::Wall(FloatRect r) : Entity(Vector2f(r.left, r.top), new RectangleShape(Vector2f(r.width, r.height))) {
	auto rect = (sf::RectangleShape*)sprite;
	rect->setFillColor(sf::Color::Red);
	rect->setOutlineColor(sf::Color::Green);
	rect->setOutlineThickness(2);
}

Brick::Brick(sf::FloatRect r, Color c) : Entity(Vector2f(r.left, r.top), new RectangleShape(Vector2f(r.width, r.height))) {
	auto rect = (sf::RectangleShape*)sprite;
	rect->setFillColor(c);
	rect->setOutlineColor(sf::Color::Yellow);
	rect->setOutlineThickness(2);
	sprite->setOrigin(Vector2f(getLocalBounds().width * 0.5, getLocalBounds().height * 0.5));
}

//std::vector<Particle> particles

void Brick::Hit() {
	hitPoint--;
	if (hitPoint <= 0) {
		world.toBeDeleted.push_back(this);
		int nbPart = Lib::rand() % 35 + 65;
		for(int i = 0; i < nbPart; i++)
			particle.addBrick(sprite->getPosition(), sprite->getFillColor());

		Game::shakeTimer += 1;

		//un rnd pour drop un bonus
		if ((Lib::rand() % 5) == 1) {
			auto bonus = new Bonus(getPosition());
			world.bonuses.push_back(bonus);
		}
		//accéder au world en extern
	}
}

Bonus::Bonus(Vector2f pos) : Entity(pos, new RectangleShape(Vector2f(50, 20))) {
	auto rect = (sf::RectangleShape*)sprite;
	rect->setOutlineThickness(2);
	sprite->setOrigin(Vector2f(getLocalBounds().width * 0.5, getLocalBounds().height * 0.5));

	speed = Vector2f(0, rand() % 3 + 4);
	type = rand() % 2;
	if (type == 0) {
		rect->setFillColor(Color::Red);
		rect->setOutlineColor(sf::Color::Red);
	}
	if (type == 1) {
		rect->setFillColor(Color::Green);
		rect->setOutlineColor(sf::Color::Green);
	}
	//std::cout << type;
}

void Bonus::Update() {
	sprite->setPosition(sprite->getPosition() + speed);
}
