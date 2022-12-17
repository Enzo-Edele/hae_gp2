#pragma once

#include <iostream>

#include <SFML/Audio.hpp>

#include "Particles.hpp"
#include "Game.hpp"

class World {
public:
	//std::vector<objet_du_world>

	void Update();

	bool UpdateCollision(Vector2i pos);

	void UpdateDeleted();
};

extern World world;