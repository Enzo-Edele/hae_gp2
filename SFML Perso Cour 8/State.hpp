#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Entity.hpp"

class Entity;

class State {
public:
	Entity* owner = nullptr;

	virtual void ApplyState() {};
	virtual void OnEvent(sf::Event& event) {};
	virtual void UpdateState() {};
};

class Idle : public State {
public:
	Idle(Entity* e) {
		owner = e;
	}

	void ApplyState() override;

	virtual void OnEvent(sf::Event& event) override;

	virtual void UpdateState() override;
};

class Cover : public State {
public:
	Cover(Entity* e) {
		owner = e;
	}

	virtual void ApplyState() override;;

	virtual void OnEvent(sf::Event& event) override;;

	virtual void UpdateState() override;;
};

class Walking : public State {
public:
	Walking(Entity* e) {
		owner = e;
	}
	virtual void ApplyState() override;

	virtual void OnEvent(sf::Event& event) override;

	virtual void UpdateState() override;
};

class Jumping : public State {
public:
	Jumping(Entity* e) {
		owner = e;
	}
	virtual void ApplyState() override;

	virtual void OnEvent(sf::Event& event) override;

	virtual void UpdateState() override;
};
class Falling : public State {
public:
	Falling(Entity* e) {
		owner = e;
	}
	virtual void ApplyState() override;

	virtual void OnEvent(sf::Event& event) override;

	virtual void UpdateState() override;
};