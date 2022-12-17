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
#include "Particles.hpp"

using namespace sf;

time_t lastModification; //a voir

void Project(){
    ContextSettings settings(0, 0, 2);
    // X: 1280 / 16 = 80
    // Y: 720 / 16 = 45
    RenderWindow window(VideoMode(80 * Game::cellSize, 45 * Game::cellSize), "Project"); 
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

	ImGui::SFML::Init(window);

	bool doHotLoad;

    double frameStart = 0;
    double frameEnd = 0.0015f;

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
            //is key released
            if (event.type == Event::KeyReleased) {
                if (event.key.code == Keyboard::Space) {

                }
                if (event.key.code == Keyboard::A) {

                }
                if (event.key.code == Keyboard::E) {

                }
            }
        }

		//HotLoad

        //is key pressed
        if (Keyboard::isKeyPressed(Keyboard::Z) ||
            Keyboard::isKeyPressed(Keyboard::Up)) {

        }
        if (Keyboard::isKeyPressed(Keyboard::S) ||
            Keyboard::isKeyPressed(Keyboard::Down)) {
            
        }
        if (Keyboard::isKeyPressed(Keyboard::D) ||
            Keyboard::isKeyPressed(Keyboard::Right)) {
            
        }
        if (Keyboard::isKeyPressed(Keyboard::Q) ||
            Keyboard::isKeyPressed(Keyboard::Left)) {
            
        }
		
        //Update

        bool t = true;
        ImGui::SFML::Update(window, sf::Time(sf::seconds(dt))); {
            //ImGui::ShowDemoWindow(&t);
        }

        window.clear();

        //Drawn

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