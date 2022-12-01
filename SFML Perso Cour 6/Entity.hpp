#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Comande.hpp"

using namespace sf;

class Entity {
public:
	Shape* sprite = nullptr; // pour le rendu
	//FloatRect localBox;//pour les collisions

	Entity(Vector2f pos, Shape* shp);

	auto getLocalBounds() const {
		return sprite->getLocalBounds();
	}

	auto getGlobalBounds() const {
		return sprite->getGlobalBounds();
	}

	auto getPosition() {
		return sprite->getPosition();
	}

	auto setPosition(const Vector2f& v) {
		sprite->setPosition(v);
	}

	void Draw(RenderWindow& win) {
		win.draw(*sprite);
	}

	virtual void Hit() {

	}
};

class Turtle {
public:
	CircleShape body;
	RectangleShape eyes[2];

	Transform trs;

	VertexArray vtx;

	Vector2f speed;

	bool isDrawing = false;

	bool isRecording = false;

	std::vector<Cmd> rec;
	std::vector<Cmd> replay;

	Turtle(Vector2f pos);

	void UpdateEyes();

	void Update(float dt);

	void Forward(int px);

	void Advance(float pixels);

	void Rotate(float deg);
	void RotateLeft(float deg);
	void RotateRight(float deg);

	void DrawBehind();

	void Earase();

	void Reset();

	void Record();

	void ReplayComande(Cmd& cmd){
		switch (cmd.id) {
		case CmdId::Advance:     Advance(cmd.data);     break;
		case CmdId::RotateLeft:  RotateLeft(cmd.data);  break;
		case CmdId::RotateRight: RotateRight(cmd.data); break;
		case CmdId::Reset:       Reset();               break;
		case CmdId::PenChange:   DrawBehind();          break;
		default:
			break;
		}
	}

	bool ReplayComandeInterpole(Cmd& cmd) {
		int speed = 5;
		switch (cmd.id) {
		case CmdId::Advance:     Advance(speed);     break;
		case CmdId::RotateLeft:  RotateLeft(speed);  break;
		case CmdId::RotateRight: RotateRight(speed); break;
		case CmdId::Reset:       Reset();               break;
		case CmdId::PenChange:   DrawBehind();          break;
		default:
			break;
		}
		cmd.data -= speed;
		return cmd.data <= 0;
	}

	void UpdateReplay() {
		if (replay.size()) {
			ReplayComande(replay[0]);
			replay.erase(replay.begin());
		}
	}

	void updateReplayInterpolated() {
		if (replay.size()) {
			bool commandFinish = ReplayComandeInterpole(replay[0]);
			if (commandFinish)
				replay.erase(replay.begin());
		}
	}

	void Draw(RenderWindow& win) {
		win.draw(vtx);
		win.draw(body);
		for (auto& e : eyes) {
			win.draw(e);
		}
	}
};
