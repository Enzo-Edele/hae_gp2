#include "Lib.hpp"

#include <filesystem>
#include <iostream>
#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <math.h>
#include "Libs/imgui/imgui.h"

//include own hpp
#include "Game.hpp"
#include "World.hpp"
#include "Entity.hpp"
#include "LevelFile.hpp"

using namespace sf;

class Player : public Entity{
public:
    Player(Vector2f pos) : Entity(pos, new RectangleShape(Vector2f(16, 16))) {
        sprite->setOrigin(Vector2f(8, 16));
    }
};

static std::vector<Color> colors = {Color(0xFF2000ff), Color(0xFF790Bff), Color(0xFFCE00ff),
    Color(0x93FF00ff), Color(0x00FFE3ff), Color(0x008CFFff), Color(0xBA0CE8ff)
};

World world;

Player* player;

void TestCour8(){
    ContextSettings settings(0, 0, 2);
    RenderWindow window(VideoMode(Game::gameX, Game::gameY), "  Grid");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    player = new Player(Vector2f(6, 6));

    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            player->OnEvent(event);

            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::KeyReleased) {
                if (event.key.code == Keyboard::Z) {
                    player->MoveGrid(Vector2f(0, -1));
                }
                if (event.key.code == Keyboard::S) {
                    player->MoveGrid(Vector2f(0, 1));
                }
                if (event.key.code == Keyboard::Q) {
                    player->MoveGrid(Vector2f(-1, 0));
                }
                if (event.key.code == Keyboard::D) {
                    player->MoveGrid(Vector2f(1, 0));
                }
                if (event.key.code == Keyboard::E) {
                    //player->SetCoordinateGtoW(Vector2f(4, 4));
                    //LevelFile::Load(world.walls);
                }
                if (event.key.code == Keyboard::A) {
                    //player->SetCoordinateWtoG(Vector2f(128, 128));
                    //LevelFile::Save(world.walls);
                }
            }
        }

        if (Mouse::isButtonPressed(Mouse::Left)) {
            Vector2i mousePos = Mouse::getPosition(window);
            Vector2f mouse = (Vector2f)mousePos;
            world.walls.push_back(new Wall(mouse));
        }

        player->Update();

        window.clear();

        for (auto& w : world.walls) {
            w->Draw(window);
        }

        player->Draw(window);

        window.display();
    }
}

int main()
{
    TestCour8();

    return 0;
}