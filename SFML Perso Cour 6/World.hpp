#pragma once

#include "Entity.hpp"
#include "Particles.hpp"

class World {
public:

	void Update();

	void UpdateCollision();

	void UpdateDeleted();
};

extern World world;