#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include<SFML/Window.hpp>
#include<filesystem>

#include "CatMull.hpp"
#include "Line.hpp"

using namespace std;

void TestTuto() {
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen()) //une frame
    {
        sf::Event event;
        while (window.pollEvent(event)) //un event  il y a d'autre mode d'interraction que poll
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
    convex.setOrigin(300, 500);

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

static int gameSizeX = 1080;
static int gameSizeY = 720;
static int groundH = 620;

static float catmullT = 0.5f;

static sf::RectangleShape ground(sf::Vector2f(gameSizeX, 2));
sf::RectangleShape canon(sf::Vector2f(20, 100));
static std::vector<sf::RectangleShape> catmullPoints;
static sf::VertexArray sight(sf::PrimitiveType::Lines);

static int cannonRotation = -45;

void TestVertex() {
    sf::ContextSettings settings(0, 0, 2);
    sf::RenderWindow window(sf::VideoMode(gameSizeX, gameSizeY), "Vertex");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    canon.setOrigin(0, 8);
    canon.setPosition(gameSizeX / 2, groundH);
    canon.setRotation(cannonRotation);
    canon.setFillColor(sf::Color::Red);

    ground.setPosition(0, groundH);
    ground.setFillColor(sf::Color::Green);

    auto plot = [](sf::Vector2f p) {
        sf::RectangleShape p0(sf::Vector2f(16, 16));
        p0.setOrigin(0, 8);
        p0.setFillColor(sf::Color::Cyan);
        p0.setOutlineColor(sf::Color::White);
        p0.setOutlineThickness(2);
        p0.setRotation(45);
        p0.setPosition(p);
        catmullPoints.push_back(p0);
    };

    plot(sf::Vector2f(100, 50));
    plot(sf::Vector2f(50, 120));
    plot(sf::Vector2f(200, 250));
    plot(sf::Vector2f(20, 300));
    plot(sf::Vector2f(200, 400));
    plot(sf::Vector2f(100, 500));

    plot(sf::Vector2f(0, 0));

    sf::RectangleShape& tPoint = catmullPoints.back();
    tPoint.setFillColor(sf::Color::Blue);

    Line l;

    std::vector<sf::Vector2f> p;
    p.push_back(sf::Vector2f(100, 50));
    p.push_back(sf::Vector2f(50, 120));
    p.push_back(sf::Vector2f(200, 250));
    p.push_back(sf::Vector2f(20, 300));
    p.push_back(sf::Vector2f(200, 400));
    p.push_back(sf::Vector2f(100, 500));
    l.SetPoint(p);

    while (window.isOpen()) //une frame
    {
        sf::Event event;
        while (window.pollEvent(event)) //un event  il y a d'autre mode d'interraction que poll
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        /*
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            cannonRotation--;
            canon.setRotation(cannonRotation);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            cannonRotation++;
            canon.setRotation(cannonRotation);
        }
        */
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            catmullT -= 0.05f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
            catmullT += 0.05f;
        }

        auto cannonPos = sf::Vertex(canon.getPosition());
        cannonPos.color = sf::Color::Red;

        sight.clear();
        sight.append(cannonPos);

        sf::Transform t;
        auto tFinal = t.rotate(cannonRotation);
        auto dest = tFinal.transformPoint(sf::Vector2f(128, 0));
        auto destVertex = sf::Vertex(dest);
        destVertex.position += cannonPos.position;
        destVertex.color = sf::Color::Red;
        sight.append(destVertex);

        sf::Vector2f calc = CatMull::Polynom2(
            catmullPoints[0].getPosition(),
            catmullPoints[1].getPosition(),
            catmullPoints[2].getPosition(),
            catmullPoints[3].getPosition(), catmullT);
        tPoint.setPosition(calc);

        window.clear();
        window.draw(ground);
        window.draw(sight);
        window.draw(canon);

        for (auto& cp : catmullPoints)
            window.draw(cp);

        l.draw(window);

        window.display();
    }
}

int main()
{
    //TestTuto();
    //TestLine();
    TestVertex();
}