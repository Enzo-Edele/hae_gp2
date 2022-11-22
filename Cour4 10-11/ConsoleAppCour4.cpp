#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include<SFML/Window.hpp>
#include<filesystem>
#include<math.h>

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

static float SightTarget = 0.5f;

static sf::RectangleShape ground(sf::Vector2f(gameSizeX, 2));
sf::RectangleShape canon(sf::Vector2f(20, 100));
static std::vector<sf::RectangleShape> catmullPoints;
static sf::VertexArray sight(sf::PrimitiveType::Lines);

static int cannonRotation = 180;

Line l;

struct Bullet {
    sf::CircleShape sph;
    float t = 0.0f;

    Bullet() {
        sph = sf::CircleShape(16);
        sph.setOrigin(16, 16);
        sph.setFillColor(sf::Color(0xF29027ff));
        sph.setOutlineThickness(2);
        sph.setOutlineColor(sf::Color(0xF33313ff));
        t = 0.0f;
    }
    void Update() {
        sf::Vector2f pos = l.InterpolateLinear(t);
        sph.setPosition(pos);
        t += 0.01;
    }
};

static std::vector<Bullet> bullets;

void TestVertex() {
    sf::ContextSettings settings(0, 0, 2);
    sf::RenderWindow window(sf::VideoMode(gameSizeX, gameSizeY), "Vertex");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    canon.setOrigin(0, 8);
    canon.setPosition(gameSizeX * 0.5f, groundH);
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

    std::vector<sf::Vector2f> p;
    p.push_back(sf::Vector2f(100, 50));
    p.push_back(sf::Vector2f(50, 120));
    p.push_back(sf::Vector2f(200, 250));
    p.push_back(sf::Vector2f(20, 300));
    p.push_back(sf::Vector2f(200, 400));
    p.push_back(sf::Vector2f(100, 500));
    l.SetPoint(p);

    std::vector<Line> mountains;

    int mntGround = 300;

    Line lineMountain;
    std::vector<sf::Vector2f> vec = {
        sf::Vector2f(0, 200), 
        sf::Vector2f(gameSizeX * 0.2f, 170),
        sf::Vector2f(gameSizeX * 0.4f, 100),
        sf::Vector2f(gameSizeX * 0.5f, 50),
        sf::Vector2f(gameSizeX * 0.75f, 60),
        sf::Vector2f(gameSizeX, 200)
    };
    lineMountain.SetPoint(vec);
    lineMountain.enableControlPointsDisplay = true;
    mountains.push_back(lineMountain);

    for (int i = 0; i < 40; i++) {
        auto m1 = mountains.back();
        m1.Translate(sf::Vector2f(0, 2 + Lib::randf() * 7));
            for (auto& o : m1.origins) {
                if (o.y < mntGround)
                    o.y += (mntGround - o.y) * (0.15f + Lib::randf() * 0.005f);
                o.x += -10 + Lib::rand() % 20;
                if (Lib::rand() % 50 == 4)
                    o.y += 3 + Lib::rand() % 30;
                if (Lib::rand() % 1000 == 4)
                    o.y -= Lib::randf() * 10;
            }
            m1.Rebake();
            mountains.push_back(m1);
    }

    while (window.isOpen()) //une frame
    {
        sf::Event event;
        while (window.pollEvent(event)) //un event  il y a d'autre mode d'interraction que poll
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::Space)
                    bullets.push_back(Bullet());
            }
        }
        
        float speed = 3.0f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            auto cannonPos = canon.getPosition();
            cannonPos.x -= speed;
            if (cannonPos.x < 0)
                cannonPos.x = 0;
            canon.setPosition(cannonPos);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            auto cannonPos = canon.getPosition();
            cannonPos.x += speed;
            if (cannonPos.x > gameSizeX)
                cannonPos.x = gameSizeX;
            canon.setPosition(cannonPos);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            SightTarget -= 0.01f;
            if (SightTarget < 0)
                SightTarget = 0;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            SightTarget += 0.01f;
            if (SightTarget > 1)
                SightTarget = 1;
        }
        p.clear();

        auto cannonPos = canon.getPosition();
        p.push_back(cannonPos);

        sf::Vector2f midPoint = sf::Vector2f(cannonPos.x * 0.5f + SightTarget * gameSizeX * 0.5f, groundH - 200);
        p.push_back(midPoint);
        p.push_back(sf::Vector2f(sf::Vector2f(SightTarget * gameSizeX, groundH)));
        l.SetPoint(p);

        sf::Vector2f dir = midPoint - cannonPos;
        double len = sqrt(dir.x * dir.x + dir.y * dir.y);
        if (len > 0) {
            dir.x /= len;
            dir.y /= len;
        }
        double angle = atan2(dir.x, dir.y);
        double angleDeg = angle / (2.0 * 3.14259) * 360;
        cannonRotation = angleDeg;

        canon.setRotation(cannonRotation);

        auto cannonVtx = sf::Vertex(canon.getPosition());
        cannonVtx.color = sf::Color::Red;

        //draw sight
        sight.clear();
        sight.append(cannonVtx);

        sf::Transform t;
        auto tFinal = t.rotate(cannonRotation);
        auto dest = tFinal.transformPoint(sf::Vector2f(128, 0));
        auto destVertex = sf::Vertex(dest);
        destVertex.position += cannonVtx.position;
        destVertex.color = sf::Color::Red;
        sight.append(destVertex);

        /*
        sf::Vector2f calc = CatMull::Polynom2(
            catmullPoints[0].getPosition(),
            catmullPoints[1].getPosition(),
            catmullPoints[2].getPosition(),
            catmullPoints[3].getPosition(), catmullT);
        tPoint.setPosition(calc);*/

        Line back1;
        std::vector<sf::Vector2f> backline1;

        window.clear();

        std::vector<sf::Color> color = {
            sf::Color(255, 255, 255),
            sf::Color(174, 174, 174),
            sf::Color(110, 110, 110),
        };

        /*for (auto& b : mountains)
            b.draw(window, sf::Color(255, 255, 255));*/

        for (auto& b : mountains)
            b.draw(window);

        window.draw(ground);
        window.draw(sight);
        window.draw(canon);

        for (auto& b : bullets) {
            b.Update();
        }

        for (auto& b : bullets)
            window.draw(b.sph);

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