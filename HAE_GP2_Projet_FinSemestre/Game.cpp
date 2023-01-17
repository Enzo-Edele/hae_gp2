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

const std::vector<Color> Game::colors = {
	Color(0x00144Fff),
	Color(0x002185ff),
	Color(0x630003ff)
};

const Vector2f Game::playerSize = Vector2f(Game::cellSize * 4, Game::cellSize * 2);

const std::vector<Vector2i> Game::spawnPos = {
	Vector2i(5, 22),
	Vector2i(80, 22),
	Vector2i(80, 10),
	Vector2i(80, 30)
};

GameState Game::state = GameState::Menu;

void Game::changeState(GameState newState) {
	state = newState;
}

//sound here

static std::vector<Sound*> sounds;
static std::unordered_map<std::string, SoundBuffer*> soundBuffers;

int Game::score = 0;
Text Game::scoreText;

int Game::lives = -1;
Text Game::livesText;

void Game::changeScore(int scoring)
{
	Game::score += scoring;
	std::string txt = "Score : " + std::to_string(Game::score);
	Game::scoreText.setString(txt);
}

void Game::changeLives(int change)
{
	Game::lives += change;
	std::string txt = "Lives : " + std::to_string(Game::lives);
	Game::livesText.setString(txt);
	//if 0 game over
}

Text Game::menuText;
Text Game::creditText1;
Text Game::creditText2;
Text Game::creditText3;

void Game::StartGame()
{
	state = GameState::Game;
	Game::changeScore(-Game::score);
	Game::changeLives(4);
	Game::menuText.setString(std::string(""));
	Game::creditText1.setString("");
	Game::creditText2.setString("");
	Game::creditText2.setString("");
}
void Game::PauseGame() {
	state = GameState::Pause;
	Game::menuText.setString(std::string("Pause"));
}
void Game::ResumeGame() {
	state = GameState::Game;
	Game::menuText.setString(std::string(""));
}
void Game::EndGame() {
	state = GameState::GameOver;
	Game::menuText.setString(std::string("Game Over Press 'R' to restart"));
	Game::creditText1.setString(std::string("Graphisme : Enzo Cloup"));
	Game::creditText2.setString(std::string("Programation : Enzo Cloup"));
	Game::creditText3.setString(std::string("Sound : Kenney Sci-Fi sound pack"));
}

void Game::playSound(const char* sound)
{
	sf::SoundBuffer* sb = soundBuffers[sound];
	if (!sb) {
		sb = new sf::SoundBuffer();
		sb->loadFromFile(sound);
		soundBuffers[sound] = sb;
	}

	auto s = new sf::Sound(*sb);
	s->play();
	sounds.push_back(s);
}

void Game::playPlayerShot() {
	playSound("Asset/Sound/PlayerShot.ogg");
}
void Game::playEnemyShot() {
	playSound("Asset/Sound/EnemyShot.ogg");
}
void Game::playPlayerDestruction() {
	playSound("Asset/Sound/PlayerDestruction.ogg");
}

void Game::playEnemyDestruction() {
	playSound("Asset/Sound/EnemyDestruction.ogg");
}



 
