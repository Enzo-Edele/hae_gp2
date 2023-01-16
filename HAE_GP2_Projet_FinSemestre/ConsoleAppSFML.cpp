#include <filesystem>
#include <iostream>
#include <string>
#include <sys/stat.h>
#include <math.h>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <imgui.h>
#include <imgui-SFML.h>

//include own hpp
#include "Lib.hpp"
#include "Game.hpp"
#include "World.hpp"
#include "Entity.hpp"
#include "Particles.hpp"
#include "Background.hpp"

using namespace sf;

time_t lastModification; //a voir

World world;

Background* background;

Player* player;

void Project(){
    ContextSettings settings(0, 0, 2);
    //map size PIXEL / CELL
    // X: 1280 / 16 = 80
    // Y: 720 / 16 = 45
    RenderWindow window(VideoMode(80 * Game::cellSize, 45 * Game::cellSize), "Project"); 
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

	ImGui::SFML::Init(window);

    Font gameFont;
    if(!gameFont.loadFromFile("Asset/Font/Figerona.ttf")) {
        printf("error can't load font");
    }

    Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("Asset/Sprite/Background.png")) {
        printf("error can't load player sprite");
    }

    Texture playerFighter;
    if (!playerFighter.loadFromFile("Asset/Sprite/fighter.png")) {
        printf("error can't load player sprite");
    }

    Texture enemyFighter;
    if (!enemyFighter.loadFromFile("Asset/Sprite/fighterE.png")) {
        printf("error can't load enemy sprite");
    }

    Texture enemyFighterSmall;
    if (!enemyFighterSmall.loadFromFile("Asset/Sprite/fighterES.png")) {
        printf("error can't load enemy sprite");
    }

    Game::scoreText.setFont(gameFont);
    Game::scoreText.setPosition(Vector2f(-180 + Game::gameCellX * Game::cellSize, 0));

    Game::livesText.setFont(gameFont);

    Game::menuText.setFont(gameFont);
    Game::menuText.setString("Press any key to start");
    Game::menuText.setPosition(Vector2f(640, 360));

    background = new Background(&backgroundTexture);

    player = new Player(
        Game::spawnPos[0],
        Game::playerSize,
        new RectangleShape(Game::playerSize),
        playerFighter);
    /*  Checkker to verify grid
    int swap = 0;
    for (int y = 0; y < Game::gameCellY; y++) {
        for (int x = 0; x < Game::gameCellX; x++) {
            world.cells.push_back(new Cell(Vector2i(x, y),
                Vector2f(Game::cellSize, Game::cellSize),
                new RectangleShape(Vector2f(Game::cellSize, Game::cellSize)),
                Game::colors[swap]));
            swap++;
            if (swap > 1)
                swap = 0;
        }
        swap++;
        if (swap > 1)
            swap = 0;
    }
*/
	bool doHotLoad;

    double frameStart = 0;
    double frameEnd = 0.0015f;

    float enemyCorvetteSpawnTimer = 2.5f;
    float enemyCruiserSpawnTimer = 5.0f;

    while (window.isOpen())
    {
		double dt = frameEnd - frameStart;
        frameStart = Lib::getTimestamp();

		doHotLoad = false;

        sf::Event event;
        while (window.pollEvent(event))
        {
			ImGui::SFML::ProcessEvent(window, event);
			sf::Time deltaTime;
            
			if (event.type == Event::Closed) {
				window.close();
			}
            //is key release
            if (event.type == Event::KeyReleased && Game::state == GameState::Menu) {
                Game::StartGame();
            }
            if (Keyboard::isKeyPressed(Keyboard::R) && Game::state == GameState::GameOver) {
                Game::StartGame();
            }
            //is key released
            if (event.type == Event::KeyReleased && Game::state == GameState::Game) {
                if (event.key.code == Keyboard::Space) {
                    player->Shoot();
                }
                if (event.key.code == Keyboard::A) {

                }
                if (event.key.code == Keyboard::E) {

                }
            }
        }

		//HotLoad

        float speed = 0.05f;
        //is key pressed
        if ((Keyboard::isKeyPressed(Keyboard::Z) ||
            Keyboard::isKeyPressed(Keyboard::Up)) && Game::state == GameState::Game) {
            player->direction.y -= speed;
        }
        if ((Keyboard::isKeyPressed(Keyboard::S) ||
            Keyboard::isKeyPressed(Keyboard::Down)) && Game::state == GameState::Game) {
            player->direction.y += speed;
        }
        if ((Keyboard::isKeyPressed(Keyboard::D) ||
            Keyboard::isKeyPressed(Keyboard::Right)) && Game::state == GameState::Game) {
            player->direction.x += speed;
        }
        if ((Keyboard::isKeyPressed(Keyboard::Q) ||
            Keyboard::isKeyPressed(Keyboard::Left)) && Game::state == GameState::Game) {
            player->direction.x -= speed;
        }
        //Mouse Buttton
        if (Mouse::isButtonPressed(Mouse::Left)) {
            //Vector2i mousePos = Mouse::getPosition(window);
            //Vector2i mousePosGrid = Vector2i(mousePos.x / Game::cellSize, mousePos.y / Game::cellSize);
            //Vector2f size(Game::cellSize, Game::cellSize);
            //world.blockers.push_back(new Blocker(mousePosGrid, size, new RectangleShape(size)));
            player->Shoot();
        }
        if (Mouse::isButtonPressed(Mouse::Right)) {
            
        }

        if (enemyCorvetteSpawnTimer < 0) {
            world.enemies.push_back(new Eneny(
                Vector2i(60, 22),
                Vector2f(Game::cellSize * 2, Game::cellSize * 2),
                new RectangleShape(Vector2f(Game::cellSize * 2, Game::cellSize * 2)),
                enemyFighterSmall,
                EnemyType::corvette));
            enemyCorvetteSpawnTimer = Lib::rand() % 1 + 3;
        }
        else if(Game::state == GameState::Game) {
            enemyCorvetteSpawnTimer -= dt;
        }
        if (enemyCruiserSpawnTimer < 0) {
            world.enemies.push_back(new Eneny(
                Vector2i(60, 22),
                Vector2f(Game::cellSize * 4, Game::cellSize * 2),
                new RectangleShape(Vector2f(Game::cellSize * 4, Game::cellSize * 2)),
                enemyFighter,
                EnemyType::cruiser));
            enemyCruiserSpawnTimer = Lib::rand() % 2 + 4;
        }
        else if (Game::state == GameState::Game) {
            enemyCruiserSpawnTimer -= dt;
        }

        //Update
        background->Update();

        player->Update(dt);

        for (auto& e : world.enemies) {
            e->Update(dt);
        }

        for (auto& p : world.playerProj) {
            p->Update();
        }

        for (auto& p : world.enemyProj) {
            p->Update();
        }

        for (auto& c : world.cells) {
            c->Lifespawn(dt);
        }

        world.UpdateDeleted();

        bool t = true;
        ImGui::SFML::Update(window, sf::Time(sf::seconds(dt))); {
            //ImGui::ShowDemoWindow(&t);
        }

        window.clear();

        //Drawn
        window.draw(background->sprite);

        for (auto& c : world.cells) {
            c->Draw(window);
        }

        for (auto& b : world.blockers) {
            b->Draw(window);
        }

        for (auto& e : world.enemies) {
            e->Draw(window);
        }

        player->Draw(window);

        for (auto& p : world.playerProj) {
            p->Draw(window);
        }

        for (auto& p : world.enemyProj) {
            p->Draw(window);
        }

        window.draw(Game::scoreText);
        window.draw(Game::livesText);
        window.draw(Game::menuText);

        ImGui::EndFrame();
        ImGui::SFML::Render(window);

        window.display();
        frameEnd = Lib::getTimestamp();
    }
    ImGui::SFML::Shutdown(window);
}

int main()
{
    Project();

    return 0;
}