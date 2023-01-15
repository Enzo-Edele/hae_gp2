#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Game.hpp"

using namespace sf;

class Background {
public:
	float speed = 0;
	Texture* texture = nullptr;
	Sprite sprite;

	Background(Texture* newTexture, int newSpeed = 2) {
		texture = newTexture;
		speed = newSpeed;
		texture->setRepeated(true);
		sprite.setTexture(*texture);
	}

	void Update() {
		sprite.setTextureRect(IntRect(sprite.getTextureRect().left + speed, 0, Game::gameX, Game::gameY));
		sprite.setTexture(*texture);
	}
};