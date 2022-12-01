#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

struct Game {
public:
	static const int gameX;
	static const int gameY;

	static const int groundHeight;

	static const std::vector<Color> colors;

	static int idxColors;
};