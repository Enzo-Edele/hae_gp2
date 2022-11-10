#include <SFML/Graphics.hpp>
#include <filesystem>
#include <iostream>

using namespace std;

void Tuto() {
    sf::RenderWindow window(sf::VideoMode(700, 400), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Red);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
}

void TextureTest() {
    sf::RenderWindow window(sf::VideoMode(700, 400), "SFML works!");
    sf::RectangleShape shape(sf::Vector2f(100, 200));
    shape.setFillColor(sf::Color::Red);

    sf::Image image;
    image.loadFromFile("asset/astolfo");

    while (window.isOpen())
    {
        

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
            shape.move(0.f, -1.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            shape.move(0.f, 1.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
            shape.move(-1.f, 0.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            shape.move(1.f, 0.f);
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
}

int main()
{
    //Tuto();
    TextureTest();

    return 0;
}