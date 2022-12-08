#include "Game.hpp"

const int Game::gameX = 1440;
const int Game::gameY = 960;

const std::vector<Color> Game::colors = { Color(0xFF2000ff), Color(0xFF790Bff), Color(0xFFCE00ff),
	Color(0x93FF00ff), Color(0x00FFE3ff), Color(0x008CFFff), Color(0xBA0CE8ff)
};

const int Game::cellSize = 16;

const float Game::gravity = 0.02f;