#include "Lib.hpp"

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
#include "LevelFile.hpp"
#include "Dijkstra.hpp"

//pour unordered map

using namespace sf;

static std::vector<Color> colors = {Color(0xFF2000ff), Color(0xFF790Bff), Color(0xFFCE00ff),
    Color(0x93FF00ff), Color(0x00FFE3ff), Color(0x008CFFff), Color(0xBA0CE8ff)
};

World world;

Player* player;

Dijkstra* dij;

void TestCour8(){
    ContextSettings settings(0, 0, 2);
    RenderWindow window(VideoMode(Game::gameX, Game::gameY), "  Grid");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    player = new Player(Vector2f(6, 6));

    Cell objective = Cell(Vector2f(10, 10), Color::Yellow);

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
                    //player->MoveGrid(Vector2f(0, -1));
                }
                if (event.key.code == Keyboard::S) {
                    //player->MoveGrid(Vector2f(0, 1));
                }
                if (event.key.code == Keyboard::Q) {
                    //player->MoveGrid(Vector2f(-1, 0));
                }
                if (event.key.code == Keyboard::D) {
                    //player->MoveGrid(Vector2f(1, 0));
                }
                if (event.key.code == Keyboard::E) {
                    //player->SetCoordinateGtoW(Vector2f(4, 4));
                    //LevelFile::Load(world.walls);
                }
                if (event.key.code == Keyboard::A) {
                    //player->SetCoordinateWtoG(Vector2f(128, 128));
                    //LevelFile::Save(world.walls);
                    dij->SetPath(player, Vector2i(objective.cx, objective.cy));
                }
                if (event.key.code == Keyboard::G) {
                    //créer un graph case valide 
                    //std vector contient les cases valide c xy de notre jeux 
                    //world.DrawValidCell(Vector2i(Game::gameCellX, Game::gameCellY));
                    world.DrawValidCell(Vector2i(30, 30));
                    
                    //puis le passer a notre structure dijkastra
                    dij = new Dijkstra(world.validCells);
                    dij->Init(Vector2i(30, 30));

                    dij->validCellDijkstra[2]->weight = 1000;
                    dij->validCellDijkstra[3]->weight = 1;
                    std::vector<Vector2i> q;
                    q.push_back(Vector2i(2, 0));
                    q.push_back(Vector2i(3, 0));
                    int idx = dij->findMin(q);
                    std::cout << idx;

                    dij->findCell(Vector2i(1, 0))->weight = 66;
                    dij->UpdateDistance(Vector2i(1, 0), Vector2i(0, 0));
                    //afficher G
                    dij->build(Vector2i(player->cx, player->cy));
                    //dij->DrawAllPath(Vector2i(30, 30));
                    dij->DrawPath(Vector2i(objective.cx, objective.cy));
                }
                if (event.key.code == Keyboard::F) {
                    world.validCells.clear();
                }
            }
        }

        if (Mouse::isButtonPressed(Mouse::Left)) {
            Vector2i mousePos = Mouse::getPosition(window);
            Vector2f mouse = (Vector2f)mousePos;
            world.walls.push_back(new Wall(mouse));
        }
        if (Mouse::isButtonPressed(Mouse::Right)) {
            Vector2i mousePos = Mouse::getPosition(window);
            Vector2f mouse = (Vector2f)mousePos;
            objective.SetCoordinateWtoG(mouse);
            objective.Update();
            objective.sprite->setPosition(Vector2f(objective.cx * Game::cellSize + 8, objective.cy * Game::cellSize + 8));
        }

        player->Update();

        window.clear();

        for (auto& w : world.walls) {
            w->Draw(window);
        }

        for (auto& vc : world.validCells) {
            vc->Draw(window);
        }

        for (auto& pc : world.pathCells) {
            pc->Draw(window);
        }

        for (auto& p : world.paths) {
            window.draw(*p);
        }

        objective.Draw(window);

        player->Draw(window);

        window.display();
    }
}

int main()
{
    TestCour8();

    return 0;
}