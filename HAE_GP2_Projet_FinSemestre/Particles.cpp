#include "Particles.hpp"

Part::Part(Vector2f pos, Color color) {
	shape.setOrigin(2, 2);
	shape.setRotation(360 * Lib::randF());
	shape.setPosition(pos);
	setSpeedBrick();
	shape.setSize(Vector2f(Lib::rand() % 20, Lib::rand() % 20));
	shape.setFillColor(color);
	life = Lib::rand() % 4 + 2;
}

Part::Part(sf::Vector2f pos, sf::Vector2f size, sf::Color color) : Part(pos, color)
{
	shape.setRotation(360 * Lib::randF()); // a calc
	shape.setSize(size);
	shape.setFillColor(color);
	life = Lib::rand() % 4 + 2;
}

void Part::Update() {
	auto pos = shape.getPosition();
	speed.x = speed.x * 0.98;
	speed.y += 0.1f;

	pos.x += speed.x;
	pos.y += speed.y;
	shape.setPosition(pos);

	life -= 0.1;
}

void Part::Draw(sf::RenderWindow& win)
{
	if (life >= 0) {
		win.draw(shape);
	}
}

void Particles::addBrick(sf::Vector2f pos, sf::Color color) {
	data.push_back(Part(pos, color));
}

void Particles::addBall(sf::Vector2f pos, sf::Vector2f size, sf::Color color){
	data.push_back(Part(pos, size, color));
}

void Particles::Update() {
	for (auto& p : data) {
		p.Update();
	}
}

void Particles::Draw(sf::RenderWindow& win) {
	for (auto& p : data) {
		p.Draw(win);
	}
}
