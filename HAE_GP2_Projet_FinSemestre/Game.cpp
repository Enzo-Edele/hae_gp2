#include <unordered_map>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Game.hpp"

using namespace sf;

const int Game::gameX = 1280;
const int Game::gameY = 720;

const int Game::cellSize = 16;

const int Game::gameCellX = Game::gameX / Game::cellSize;
const int Game::gameCellY = Game::gameY / Game::cellSize;

const std::vector<Color> Game::colors = { Color(0xFF2000ff), Color(0xFF790Bff), Color(0xFFCE00ff),
	Color(0x93FF00ff), Color(0x00FFE3ff), Color(0x008CFFff), Color(0xBA0CE8ff)
};

//sound here

static std::vector<Sound*> sounds;
static std::unordered_map<std::string, SoundBuffer*> soundBuffers;

void Game::playSound(const char* sound)
{
}

//image + texture here
