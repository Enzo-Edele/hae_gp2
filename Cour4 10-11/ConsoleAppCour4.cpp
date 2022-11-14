#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

void TestTuto() {
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

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

    int here = 0;
}

void TestLine() {
    sf::RenderWindow window(sf::VideoMode(800, 500), "SFML works!");
    sf::ConvexShape convex;

    convex.setPointCount(6);

    convex.setPoint(0, sf::Vector2f(10, 10));
    convex.setPoint(1, sf::Vector2f(160, 10));
    convex.setPoint(2, sf::Vector2f(120, 50));
    convex.setPoint(5, sf::Vector2f(50, 50));
    convex.setPoint(3, sf::Vector2f(100, 120));
    convex.setPoint(4, sf::Vector2f(70, 120));
    convex.setFillColor(sf::Color::Red);

    sf::RectangleShape rect(sf::Vector2f(150, 100));
    rect.setFillColor(sf::Color::Black);
    rect.setOutlineThickness(10);
    rect.setOutlineColor(sf::Color::Yellow);
    rect.setPosition(10, 10);

    sf::Texture texture;
    if (!texture.loadFromFile("Assets/Galactica.png", sf::IntRect(10, 10, 150, 100)))
    {
        std::cout << "error texture" << "\n";
    }
    else {
        texture.loadFromFile("Assets/Galactica.png");
    }
    texture.setSmooth(true);
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setScale(sf::Vector2f(0.5f, 0.5f));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
                sprite.move(sf::Vector2f(0, -1));
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                sprite.move(sf::Vector2f(0, 1));
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
                sprite.move(sf::Vector2f(-1, 0));
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                sprite.move(sf::Vector2f(1, 0));
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                sprite.rotate(45.f);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
                sprite.rotate(-45.f);
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        //window.draw(convex);
        //window.draw(rect);
        window.draw(sprite);
        window.display();
    }

    int here =  0;
}

int main()
{
    //TestTuto();
    TestLine();
}