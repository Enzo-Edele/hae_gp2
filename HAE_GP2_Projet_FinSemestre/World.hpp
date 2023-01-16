#pragma once

#include <iostream>

#include <SFML/Audio.hpp>

#include "Particles.hpp"
#include "Game.hpp"
#include "Entity.hpp"

class World {
public:
	std::vector<Cell*> cells;
	std::vector<Blocker*> blockers;
	std::vector<Eneny*> enemies;
	std::vector<Projectile*> playerProj;
	std::vector<Projectile*> enemyProj;

	std::vector<Eneny*> enemiesToBeDeleted;
	std::vector<Projectile*> playerProjToBeDeleted;
	std::vector<Projectile*> enemyProjToBeDeleted;

	void Update();

	bool UpdateCollisionPlayer(Vector2i pos);
	bool UpdateCollisionPlayerDestroy(Vector2i pos);

	bool UpdateCollisionEnemy(Vector2i pos);
	bool UpdateCollisionEnemyDestroy(Vector2i pos);

	bool UpdateCollisionProjectile(Vector2i pos);

	void UpdateDeleted();

	void Clear();
};

extern World world;