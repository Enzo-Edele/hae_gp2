#pragma once

using namespace sf;

struct Game {
public:
	static const int gameX;
	static const int gameY;

	static const int cellSize;

	static const int gameCellX;
	static const int gameCellY;

	static const std::vector<Color> colors;

	static void playSound(const char* sound);

	//play sound fct
};