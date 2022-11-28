#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Lib.hpp"

struct Part {
	float life = 10;
	sf::Vector2f speed;
	sf::RectangleShape shape = sf::RectangleShape(sf::Vector2f(4, 4));

	Part(sf::Vector2f pos, sf::Color color);
	Part(sf::Vector2f pos, sf::Vector2f size, sf::Color);

	void Update();
	void Draw(sf::RenderWindow& win);

	void setSpeedBrick(){
		sf::Vector2f pos = shape.getPosition();
		sf::Vector2f dest = Vector2f(pos.x + Lib::rand() % 10 - 5, pos.y + Lib::rand() % 10 - 5);
		auto dir = pos - dest;
		Lib::safeNormalize(dir);
		float sp = 2.0f;
		dir.x *= sp;
		dir.y *= sp;
		speed = dir;
	}
	void setSpeedBall() {
		sf::Vector2f pos = shape.getPosition();
		sf::Vector2f dest = Vector2f(pos.x , pos.y + Lib::rand() % - 1);
		auto dir = pos - dest;
		Lib::safeNormalize(dir);
		float sp = 2.0f;
		dir.x *= sp;
		dir.y *= sp;
		speed = dir;
	}
};

class Particles {
public:
	std::vector<Part> data;

	void addBrick(sf::Vector2f pos, sf::Color color);
	void addBall(sf::Vector2f pos, sf::Vector2f size, sf::Color color);
	void Update();
	void Draw(sf::RenderWindow& win);
};