#include "Lib.hpp"

#include <filesystem>
#include <iostream>
#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <math.h>
#include <sys/stat.h>

#include <imgui.h>
#include <imgui-SFML.h>

//include own hpp
#include "Catmull.hpp"
#include "Line.hpp"
#include "Entity.hpp"
#include "Game.hpp"
#include "World.hpp"
#include "Particles.hpp"
#include "Comande.hpp"
#include "CommandeFile.hpp"

using namespace sf;

static std::vector<Color> colors = {Color(0xFF2000ff), Color(0xFF790Bff), Color(0xFFCE00ff),
    Color(0x93FF00ff), Color(0x00FFE3ff), Color(0x008CFFff), Color(0xBA0CE8ff)
};

Turtle* turtle;

int speed = 1;

time_t lastModification;

void TestCour6(){

    ContextSettings settings(0, 0, 2);
    RenderWindow window(VideoMode(Game::gameX, Game::gameY), "Echec");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

	ImGui::SFML::Init(window);

    turtle = new Turtle(Vector2f(Game::gameX * 0.5, Game::gameY * 0.5));

	bool doHotLoad;

	static int timer = 0;

    double frameStart = 0;
    double frameEnd = 0.0015f;

	float reloadTimer = 20.0f;

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
            
			//ImGui::Begin();
			//ImGui::Button();
			//ImGui::EndFrame;
			//ImGui::End;

			if (event.type == Event::Closed) {
				window.close();
				
			}
            if (event.type == Event::KeyReleased) {
                if (event.key.code == Keyboard::Space)
                    turtle->DrawBehind();
				if (event.key.code == Keyboard::R) {
					turtle->Record();
					std::cout << "rec";
				}
                if (event.key.code == Keyboard::P)
                    turtle->replay = turtle->rec;
                if (event.key.code == Keyboard::E) {
                    Game::idxColors += 1;
                    if (Game::idxColors == 7) Game::idxColors = 0;
                }
                if (event.key.code == sf::Keyboard::T) {
                    turtle->replay = { {CmdId::PenChange,100},{CmdId::Advance,100} };
                }
                if (event.key.code == Keyboard::U) {
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
				if (event.key.code == Keyboard::K) {
					CommandeFile::Save("Save1.txt", turtle->rec);
					std::cout << "save";
				}
				if (event.key.code == Keyboard::L) {
					doHotLoad = true;
				}

				if (event.key.code == Keyboard::V) {
					turtle->replay.clear();
					turtle->replay = CommandeFile::LoadScript("Save2.txt");
					std::cout << "load";
				}
            }
        }

		timer++;
		if (timer > 60) {
			struct stat ts = {};
			stat("Save1.txt", &ts);
			doHotLoad = false;
		}

		if (doHotLoad) {
			turtle->replay.clear();
			turtle->replay = CommandeFile::Load("Save1.txt");
			std::cout << "load";

			//struct stat ts = {};

			//stat("save1.txt", &ts);
			//lastModification = ts.st_mtime;
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
		
        

        turtle->Update(dt); //mettre dt en arg plus revoir corr de update

        bool t = true;
        ImGui::SFML::Update(window, sf::Time(sf::seconds(dt))); {
            ImGui::ShowDemoWindow(&t);
        }

        window.clear();

        turtle->Draw(window);

        ImGui::EndFrame();
        ImGui::SFML::Render(window);

        window.display();
        frameEnd = Lib::getTimestamp();
    }
    ImGui::SFML::Shutdown(window);
}

int main()
{
    TestCour6();

    return 0;
}