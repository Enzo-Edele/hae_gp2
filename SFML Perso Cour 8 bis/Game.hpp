#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

struct Game {
public:
	static const int gameX;
	static const int gameY;

	static const std::vector<Color> colors;

	static const int cellSize;

	static const int gameCellX;
	static const int gameCellY;

	static const float gravity;
};