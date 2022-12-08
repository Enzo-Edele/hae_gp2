#pragma once

#include "Entity.hpp"

class World {
public:

	Entity* player;

	std::vector<Entity*> walls;

	void Update();

	bool UpdateCollision(float cx, float cy);

	void UpdateDeleted();
};

extern World world;