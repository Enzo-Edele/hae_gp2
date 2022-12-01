#include "Entity.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

#include "Lib.hpp"
#include "World.hpp"
#include "Game.hpp"
#include "Particles.hpp"
#include "Comande.hpp"

Entity::Entity(Vector2f pos, Shape* shp) {
	this->sprite = shp;
	sprite->setPosition(pos);
}

//pour appeler construct parend on lui passe en valeur les arg de l'enfant puis on peut ajouter dans l'enfant

Turtle::Turtle(Vector2f pos)
{
	body = CircleShape(24);
	body.setOrigin(body.getRadius(), body.getRadius());
	body.setPosition(pos);
	body.setFillColor(Color::Red);
	body.setOutlineColor(Color::Yellow);
	body.setOutlineThickness(2);
	trs.translate(body.getPosition());

	for (auto& e : eyes) {
		e = RectangleShape(Vector2f(4, 10));
		e.setOrigin(2, 5);
		e.setFillColor(Color::Cyan);
	}

	speed = Vector2f(0, -1);

	vtx.setPrimitiveType(Lines);

	UpdateEyes();
}

void Turtle::UpdateEyes() {
	{
		auto t = trs;
		Transform transed = t.translate(Vector2f(6, -10));
		auto tCenter = transed.transformPoint(0, 0);
		eyes[0].setPosition(tCenter);
	}
	{
		auto t = trs;
		Transform transed = t.translate(Vector2f(-6, -10));
		auto tCenter = transed.transformPoint(0, 0);
		eyes[1].setPosition(tCenter);
	}
}

void Turtle::Forward(int px)
{
	trs.translate(Vector2f(0, -px));
	auto tCenter = trs.transformPoint(0, 0);
	body.setPosition(tCenter);

	if (isDrawing) {
		vtx.append(Vertex(body.getPosition(), Game::colors[Game::idxColors]));
	}
}

void Turtle::Advance(float pixels)  //do the same things as forward but better
{
	trs = trs.translate(Vector2f(0, -pixels));
	body.setPosition(trs.transformPoint(0, 0));

	if (isDrawing) {
		vtx.append(Vertex(body.getPosition(), Game::colors[Game::idxColors]));
	}

	if (isRecording) {
		rec.push_back(Cmd(CmdId::Advance, pixels));
	}
}

void Turtle::Rotate(float deg)
{
	trs.rotate(deg);
	body.rotate(deg);
}

void Turtle::RotateLeft(float deg)
{
	Rotate(deg);
	if (isRecording) {
		rec.push_back(Cmd(CmdId::RotateLeft, deg));
	}
}

void Turtle::RotateRight(float deg)
{
	Rotate(deg);
	if (isRecording) {
		rec.push_back(Cmd(CmdId::RotateRight, deg));
	}
}



void Turtle::DrawBehind()
{
	if (isDrawing) isDrawing = false;
	else isDrawing = true;
	if (isRecording) rec.push_back(Cmd(CmdId::PenChange, 0));
}

void Turtle::Earase()
{
	vtx.clear();
}

void Turtle::Reset()
{
	isDrawing = false;

	vtx.clear();
	trs = Transform();
	trs.translate(Game::gameX * 0.5f, Game::gameY * 0.5);
	body.setPosition(trs.transformPoint(Vector2f(0, 0)));
	UpdateEyes();

	if (isRecording) rec.push_back(Cmd(CmdId::Reset, 0));
}

void Turtle::Record()
{
	if (isRecording) isRecording = false;
	else isRecording = true;
}

void Turtle::Update(float dt)
{
	UpdateEyes();

	if (isRecording) {

	}
	else if (replay.size()) {
		updateReplayInterpolated();
	}
}
