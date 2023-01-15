#pragma once

using namespace sf;

enum class GameState : int {
	Menu,
	Game,
	GameOver,
};

struct Game {
public:
	static const int gameX;
	static const int gameY;

	static const int cellSize;

	static const int gameCellX;
	static const int gameCellY;

	static const std::vector<Color> colors;

	static const Vector2f playerSize;

	static const std::vector<Vector2i> spawnPos;

	static GameState state;
	static void changeState(GameState newState);

	static int score;
	static Text scoreText;

	static int lives;
	static Text livesText;

	static void changeScore(int scoring);

	static void changeLives(int scoring);

	static void playSound(const char* sound);

	static void playPlayerShot();

	static void playEnemyShot();

	static void playPlayerDestruction();

	static void playEnemyDestruction();

	//play sound fct
};