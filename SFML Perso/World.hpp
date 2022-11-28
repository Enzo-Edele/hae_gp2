#pragma once

#include "Entity.hpp"
#include "Particles.hpp"

class World {
public:
	std::vector<Ball*> balls;
	std::vector<Entity*> statics;

	std::vector<Pad*> pads;
	std::vector<Bonus*> bonuses;

	std::vector<Entity*> toBeDeleted;
	std::vector<Bonus*> bonusDeleted;

	void Update();

	void UpdateCollision();

	void UpdateDeleted();
};

extern World world;
extern Particles particle;