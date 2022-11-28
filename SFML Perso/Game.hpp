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

	static const int padX;
	static const int padY;

	static int lives;

	static float shakeTimer;

	//faire une ref au son
	//static SoundBuffer startSound;
	//static Sound soundPad;
};