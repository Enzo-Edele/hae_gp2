#include "Lib.hpp"

#include <filesystem>
#include <iostream>
#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <math.h>

//include own hpp
#include "Game.hpp"
#include "World.hpp"
#include "Entity.hpp"

using namespace sf;

class Player : public Entity{
public:
    Player(Vector2f pos) : Entity(pos, new RectangleShape(Vector2f(16, 16))) {
        
    }
};

static std::vector<Color> colors = {Color(0xFF2000ff), Color(0xFF790Bff), Color(0xFFCE00ff),
    Color(0x93FF00ff), Color(0x00FFE3ff), Color(0x008CFFff), Color(0xBA0CE8ff)
};

Player* player;

void TestCour7(){
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
                    player->SetCoordinateGtoW(Vector2f(4, 4));
                }
                if (event.key.code == Keyboard::A) {
                    player->SetCoordinateWtoG(Vector2f(128, 128));
                }
            }
        }

        if(Keyboard::isKeyPressed(Keyboard::Up)) {
            player->MovePixel(Vector2f(0, -0.2));
        }
        if (Keyboard::isKeyPressed(Keyboard::Down)) {
            player->MovePixel(Vector2f(0, 0.2));
        }
        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            player->MovePixel(Vector2f(-0.2, 0));
        }
        if (Keyboard::isKeyPressed(Keyboard::Right)) {
            player->MovePixel(Vector2f(0.2, 0));
        }

        player->Update();

        window.clear();

        player->Draw(window);

        window.display();
    }
}

int main()
{
    TestCour7();

    return 0;
}