#include "Lib.hpp"

#include <filesystem>
#include <iostream>
#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <math.h>

//include own hpp
#include "Catmull.hpp"
#include "Line.hpp"
#include "Entity.hpp"
#include "Game.hpp"
#include "World.hpp"
#include "Particles.hpp"
#include "Comande.hpp"

using namespace sf;



static std::vector<Color> colors = {Color(0xFF2000ff), Color(0xFF790Bff), Color(0xFFCE00ff),
    Color(0x93FF00ff), Color(0x00FFE3ff), Color(0x008CFFff), Color(0xBA0CE8ff)
};

Turtle* turtle;
int speed = 1;

void TestCour6(){
    ContextSettings settings(0, 0, 2);
    RenderWindow window(VideoMode(Game::gameX, Game::gameY), "Brick");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    turtle = new Turtle(Vector2f(Game::gameX * 0.5, Game::gameY * 0.5));

    double frameStart = 0;
    double frameEnd = 0.0015f;
    while (window.isOpen())
    {
        //faire un dt 
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::KeyReleased) {
                if (event.key.code == Keyboard::Space)
                    turtle->DrawBehind();
                if (event.key.code == Keyboard::R)
                    turtle->Record();
                if (event.key.code == Keyboard::P)
                    turtle->replay = turtle->rec;
                if (event.key.code == Keyboard::E) {
                    Game::idxColors += 1;
                    if (Game::idxColors == 7) Game::idxColors = 0;
                }
                if (event.key.code == sf::Keyboard::K) {
                    turtle->replay = { {CmdId::PenChange,100},{CmdId::Advance,100} };
                }
                if (event.key.code == Keyboard::R) {
                    turtle->replay = {
                        Cmd(CmdId::PenChange, 1),
                        Cmd(CmdId::Advance, 100),
                        Cmd(CmdId::RotateLeft, 90),
                        Cmd(CmdId::Advance, 100),
                        Cmd(CmdId::RotateLeft, 90),
                        Cmd(CmdId::Advance, 100),
                        Cmd(CmdId::RotateLeft, 90),
                        Cmd(CmdId::Advance, 100),
                        Cmd(CmdId::RotateLeft, 90),
                    };
                }
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Z) ||
            Keyboard::isKeyPressed(Keyboard::Up)) {
            //turtle->Forward(speed);
            turtle->Advance(5);
        }
        if (Keyboard::isKeyPressed(Keyboard::S) ||
            Keyboard::isKeyPressed(Keyboard::Down)) {
            //turtle->Forward(-speed);
            //turtle->Advance(-5);
        }
        if (Keyboard::isKeyPressed(Keyboard::D) ||
            Keyboard::isKeyPressed(Keyboard::Right)) {
            //turtle->Rotate(speed);
            turtle->RotateRight(5);
        }
        if (Keyboard::isKeyPressed(Keyboard::Q) ||
            Keyboard::isKeyPressed(Keyboard::Left)) {
            //turtle->Rotate(-speed);
            turtle->RotateLeft(-5);
        }
        if (Keyboard::isKeyPressed(Keyboard::X)) {
            turtle->Reset();
        }
        if (Keyboard::isKeyPressed(Keyboard::Add)) {
            speed += 1;
            if (speed > 20) speed = 20;
        }
        if (Keyboard::isKeyPressed(Keyboard::Subtract)) {
            speed -= 1;
            if (speed < 1) speed = 1;
        }

        turtle->Update(0); //mettre dt en arg plus revoir corr de update

        window.clear();

        turtle->Draw(window);

        window.display();
    }
}

int main()
{
    TestCour6();

    return 0;
}