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

using namespace sf;

static float sightTarget = 0.5f;

static RectangleShape ground(Vector2f(Game::gameX, 2));
static RectangleShape cannon(Vector2f(80, 16));
static std::vector<RectangleShape> catmullPoints;
static VertexArray sight(PrimitiveType::Lines);
static Line l;

//une struct bullet
struct Bullet {
    //circle shape
    CircleShape shape;
    //t (distance parcourue)
    float t = 0.0f;

    //un contructeur : taille du cercle, origin, color, outline color and thick, t à 0
    Bullet(){
        shape = CircleShape(16);
        shape.setOrigin(16, 16);
        shape.setFillColor(Color::Red);
        shape.setOutlineColor(Color::Magenta);
        shape.setOutlineThickness(2);
        t = 0.0f;
    }
    //update : vector pos interpoler t*2, set posotion à pos, incrémenter t de 0.01
    void Update() {
        Vector2f pos = l.interpolateLinear(t * 2);
        shape.setPosition(pos);
        t += 0.01f;
    }
};
//tab vec bullet
static std::vector<Bullet> bullets;

//cannonRotation
static float cannonRotation = -45;

void TestSFML() {
    sf::ContextSettings settings(0, 0, 2);
    sf::RenderWindow window(sf::VideoMode(Game::gameX, Game::gameY), "SFML works!");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    //set cannon origin(0, cannon.y / 2)
    cannon.setOrigin(0, 8);
    //set cannon position(X * 0.5, groundHeight
    cannon.setPosition(Game::gameX * 0.5f, Game::groundHeight);
    //set cannon rotation
    cannon.setRotation(cannonRotation);

    //set ground position
    ground.setPosition(0, Game::groundHeight);
    //set ground color
    ground.setFillColor(Color::Green);

    //texture du cannon
    Texture cannonTexture;
        //bool to check if path is ok
    bool textOk = cannonTexture.loadFromFile("Asset/TextureCannon.png");
    //if!bool : cout can't load, return
    if (!textOk) {
        std::cout << "texture not found";
        return;
    }
    //cannon set texture
    cannon.setTexture(&cannonTexture, true);

    //on a déclarer le tableau catmullpoint plus haut
    //insérer des point dans catmullPoints
    auto points = [&](Vector2f p) {
        RectangleShape pShp(Vector2f(16, 16));
        pShp.setOrigin(8, 8);
        pShp.setFillColor(Color::Blue);
        pShp.setOutlineColor(Color::White);
        pShp.setOutlineThickness(2);
        pShp.setRotation(45);
        pShp.setPosition(p);
        catmullPoints.push_back(pShp);
    };
    //add thing to points

    //useless tpoint

    //tab vec vector2f pour le signt
    std::vector<Vector2f> sightPoint;
    
    //mountains
    //tab vec line pour les montagne
    std::vector<Line> mountains;

    //int mntGround = hauteur designe ~200 400
    int mountGround = 200;
    //Line mntLine
    Line mountain;
    //tab vec de vector2f vec : listez des point pour faire une ligne bckg
    std::vector<Vector2f> vec{
        Vector2f(0, 200), Vector2f(Game::gameX * 0.23f, 180), Vector2f(Game::gameX * 0.5f, 80), Vector2f(Game::gameX * 0.7f, 120), Vector2f(Game::gameX, 200)
    };

    //mtnline set point vec
    mountain.SetPoint(vec);
    //mountains pushback mtnline
    mountains.push_back(mountain);

    //for   i 0  < (nb ligne voulu)
        // n1 = mountains back
        // n1 translate vector2f (0, 2 + randf * 7)
        // foreach o  n1.origins
            //if(o.y < mntground : float diff (mntground - o.y) * (0.15f + Lib::randF() * 0.005f)      o.y += diff
            //o.x + -10 + rand % 20
            // if(rand % 50 == 4  : o.y + 3 + rand % 30
            // if rand % 1000 == 4  :  o.y - randf * 20
        //n1.heightmap 1 + 5 + randf * 8
        //n1 rebake
        // mountains.pushback n1
    for (int i = 0; i < 50; i++) {
        auto n1 = mountains.back();
        n1.Translate(Vector2f(0, 2 + Lib::randF() * 7));
        for (auto& o : n1.origins) {
            if (o.y < mountGround) {
                float diff = (mountGround - o.y) * (0.15f + Lib::randF() * 0.005f);
                o.y += diff;
            }
            o.x += -10 + Lib::rand() % 20;
            if (Lib::rand() % 50 == 4) {
                o.y += 3 + Lib::rand() % 30;
            }
            if (Lib::rand() % 1000 == 4) {
                o.y -= Lib::randF() * 20;
            }
        }
        n1.heightMap[1] += 5 + Lib::randF() * 8;
        n1.Rebake();
        mountains.push_back(n1);
    }

    //foreach m : mountains
        //m colorMinMax 0   color green or white
        //m colorMinMax 1   color green or white
    for (auto& m : mountains) {
        m.colorMinMax[0] = Color::White;//Color(0xE6EEDEff);//
        m.colorMinMax[1] = Color::Green;//Color(0x8F8688ff);//
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) { // ONE EVENT
            if (event.type == sf::Event::Closed)
                window.close();
            //if keyrelease : key space : bullet pushback Bullet create a bullet
            if (event.KeyReleased) {
                if (event.key.code == Keyboard::Space) {
                    bullets.push_back(Bullet());
                }
            }
        }

        float speed = 3.0;
        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            auto cannonPos = cannon.getPosition();
            cannonPos.x -= speed;
            if (cannonPos.x < 0) cannonPos.x = 0;
            cannon.setPosition(cannonPos);
        }
        //if left
            //cannonPos get cannon pos
            // =+ SPEED
            // inf 0 : = 0
            // set pos
        if (Keyboard::isKeyPressed(Keyboard::Right)) {
            auto cannonPos = cannon.getPosition();
            cannonPos.x += speed;
            if (cannonPos.x > Game::gameX) cannonPos.x = Game::gameX;
            cannon.setPosition(cannonPos);
        }
        //if right
            //cannonPos get cannon pos
            // =+ SPEED
            // SUP A GAME X : = gamex
            // set pos
        if (Keyboard::isKeyPressed(Keyboard::Up)) {
            sightTarget -= 0.01;
            if (sightTarget < 0) sightTarget = 0;
        }
        //if up
            // sight target - 0.01
            // if < 0 = 0
        if (Keyboard::isKeyPressed(Keyboard::Down)) {
            sightTarget += 0.01;
            if (sightTarget > 1) sightTarget = 1;
        }
        //if down
            // sight target + 0.01
            // if > 1 = 1

        //clear sight tab
        sightPoint.clear();
        //cannonpos get cannonpos
        auto cannonPos = cannon.getPosition();
        //sight pushback cannonpos
        sightPoint.push_back(cannonPos);

        //vector2f midpoint = cannonpos * 0.5 + sighttarget * gamewith * 0.5f, ground - 200
        Vector2f midPoint = Vector2f(cannonPos.x * 0.5 + sightTarget * Game::gameX * 0.5, Game::groundHeight - 200);
        //sight pushback midpoint
        sightPoint.push_back(midPoint);
        //sight pushback sight target * gamewidth, groundheight
        sightPoint.push_back(Vector2f(sightTarget * Game::gameX, Game::groundHeight));

        //set point in line declare in static
        l.SetPoint(sightPoint);

        //vector2f dir midpoint - cannonpos
        Vector2f dir = midPoint - cannonPos;

        //Do cannon rotation
        //double len sqrt(dir)
        double len = sqrt(dir.x * dir.x + dir.y * dir.y);
        if (len > 0) {
            dir.x /= len;
            dir.y /= len;
        }
        //if len > 0
            //dirx /len
            //diry/len
        //double angle = atan2
        double angle = atan2(dir.y, dir.x);
        //double angleDeg = angle /(2 * pi) * 360
        double angleDegree = angle / (2.0f * 3.14159) * 360;
        //cannonRot = angleDeg
        cannonRotation = angleDegree;
        //set cannonRot
        cannon.setRotation(cannonRotation);

        //vertex cannonvertex = vertex getcannonpos
        Vertex cannonVertex = cannon.getPosition();
        //cannonvtx.color = red
        cannonVertex.color = Color::Red;

        //draw sight
        //sight clear
        sight.clear();
        //sight append cannonvtx
        sight.append(cannonVertex);

        //transform t
        Transform t;
        //tfinal t.rotate cannonrot
        auto tfinal = t.rotate(cannonRotation);
        //dest = tfinal.transformpoint vector2 128 0
        auto dest = tfinal.transformPoint(Vector2f(128, 0));
        //destvert vertex dest
        auto destVert = Vertex(dest);
        //destvert position += cannonvtx position
        destVert.position += cannonVertex.position;
        //destvert color = red
        destVert.color = Color::Red;
        //sight append dest vert
        sight.append(destVert);

        //window clear()
        window.clear();

        //forech mountains : m.draw()
        for (auto& m : mountains) {
            m.Draw(window);
        }

        //draw ground
        window.draw(ground);
        //draw sight
        window.draw(sight);
        //draw cannon
        window.draw(cannon);

        //foreach bullet update
        for (auto& b : bullets) {
            b.Update();
        }
        //foreach bullet draw
        for (auto& b : bullets) {
            window.draw(b.shape);
        }

        window.display();
    }
}

World world;
Particles particle;

static int padX = 144;
static int padY = 24;
static Pad* pad = nullptr;

static int brickX = 80;
static int brickY = 20;

static int ballSize = 12;
static Ball* ball = nullptr;

static std::vector<Color> colors = {Color(0xFF2000ff), Color(0xFF790Bff), Color(0xFFCE00ff),
    Color(0x93FF00ff), Color(0x00FFE3ff), Color(0x008CFFff), Color(0xBA0CE8ff)
};

static std::vector<Brick> Lines;

void TestProject() {
    ContextSettings settings(0, 0, 2);
    RenderWindow window(VideoMode(Game::gameX, Game::gameY), "Brick");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    ground.setPosition(0, Game::groundHeight);
    ground.setFillColor(Color(0x62F6D2ff));

    pad = new Pad(Vector2f(Game::gameX * 0.5, Game::groundHeight));
    ball = new Ball(pad);

    world.pads.push_back(pad);
    world.balls.push_back(ball);
    world.statics.push_back(pad);

    auto wl = new Wall(FloatRect(Vector2f(-3, 0), Vector2f(6, Game::gameY)));
    world.statics.push_back(wl);
    auto wr = new Wall(FloatRect(Vector2f(-3 + Game::gameX, 0), Vector2f(6, Game::gameY)));
    world.statics.push_back(wr);
    auto wh = new Wall(FloatRect(Vector2f(3, -3), Vector2f(Game::gameX + 6, 6)));
    world.statics.push_back(wh);

    //auto br0 = new Brick(FloatRect(Vector2f(50, 50), Vector2f(brickX, brickY)));
    //world.statics.push_back(br0);

    for (int x = 0; x < 7; x++) {
        for (int y = 0; y < 14; y++) {
            auto br = new Brick(FloatRect(Vector2f((64 + Game::padX / 2) + y * brickX, 64 + x * brickY), Vector2f(brickX, brickY)), colors[x]);
            world.statics.push_back(br);
            //push back dans une ligne
        }
        //push back la ligne
    }

    //Game::soundPad.setBuffer(Game::startSound);
    //if (!Game::startSound.loadFromFile("Asset/impactPad.ogg")) {
    //    return;
    //}

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyReleased) {
            }
        }

        float speed = 7.0f;
        
        if (Keyboard::isKeyPressed(Keyboard::Right)) {
            //Vector2f newPos = pad.position;
            //newPos.x += speed;
            //pad.Move(newPos);
            pad->MoveRight();
        }
        else if (Keyboard::isKeyPressed(Keyboard::Left)) {
            //Vector2f newPos = pad.position;
            //newPos.x -= speed;
            //pad.Move(newPos);
            pad->MoveLeft();
        }
        else if (Keyboard::isKeyPressed(Keyboard::Up)) {
            //balls.push_back(Ball(Vector2f(gameSizeX * 0.5, groundHeight - 30), Vector2f(ballSize, ballSize)));
        }
        else if (Keyboard::isKeyPressed(Keyboard::Down)) {
            //Game::soundPad.play();
            //Game::shakeTimer = 5;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Space)) {
            auto pad = ball->hooked;
            if (pad) {
                ball->hooked = nullptr;
                auto dir = ball->getPosition() - pad->getPosition();
                Lib::safeNormalize(dir);
                float sp = 10.0f;
                dir.x *= sp;
                dir.y *= sp;
                ball->speed = dir;
            }
        }

        if (Game::shakeTimer > 0) {
            window.setPosition(Vector2i(100 + Lib::rand() % 25, 100 + Lib::rand() % 25));
            Game::shakeTimer -= 0.1f;
        }
        else if(Game::shakeTimer < 0){
            Game::shakeTimer = 0;
        }

        ball->Update();
        world.Update();
        particle.Update();

        window.clear();
        
        window.draw(ground);

        for (auto st : world.statics)
            st->Draw(window);

        for (auto b : world.bonuses)
            b->Draw(window);

        pad->Draw(window);
        ball->Draw(window);

        particle.Draw(window);

        window.display();

        if (ball->getPosition().y > Game::gameY) {
            Game::lives--;
            if (Game::lives >= 0) {
                ball->initPos(pad);
                std::cout << Game::lives;
            }
        }
    }
}

void Reset(){
    //clear world

    //world.balls.push_back(ball);
    //world.statics.push_back(pad);

    //pad = new Pad(Vector2f(Game::gameX * 0.5, Game::groundHeight));
    //ball = new Ball(pad);

    //for (int x = 0; x < 7; x++) {
    //    for (int y = 0; y < 14; y++) {
    //        auto br = new Brick(FloatRect(Vector2f(50 + y * brickX, 50 + x * brickY), Vector2f(brickX, brickY)), colors[x]);
    //        world.statics.push_back(br);
    //    }
    //}
}

int main()
{
    //TestSFML();

    TestProject();

    return 0;
}