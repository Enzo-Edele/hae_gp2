#include "World.hpp"

void World::Update() {
	UpdateDeleted();
}

bool World::UpdateCollisionPlayer(Vector2i pos) {
	if (pos.x > (Game::gameX / Game::cellSize) - 5 || pos.x < 0) {
		return true;
	}
	if (pos.y < 0 || pos.y >= (Game::gameY / Game::cellSize) - 2) {
		return true;
	}
	//foreach collider
	for (auto& b : blockers) {
		if (b->posGrid.x >= pos.x && b->posGrid.x <= pos.x + 4 &&
			b->posGrid.y >= pos.y && b->posGrid.y <= pos.y + 2
			) {
			return true;
		}
	}

	return false;
}
bool World::UpdateCollisionPlayerDestroy(Vector2i pos) {
	for (auto& e : enemies) {
		if (e->posGrid.x >= pos.x && e->posGrid.x <= pos.x + 4 &&
			e->posGrid.y >= pos.y && e->posGrid.y <= pos.y + 2
			) {
			return true;
		}
	}
	for (auto& pe : enemyProj) {
		if (pe->posGrid.x >= pos.x && pe->posGrid.x <= pos.x + 7.5 &&
			pe->posGrid.y >= pos.y && pe->posGrid.y <= pos.y + 3.8
			) {
			return true;
		}
	}

	return false;
}

bool World::UpdateCollisionEnemy(Vector2i pos) {
	if (pos.x > (Game::gameX / Game::cellSize) || pos.x < -7) {
		return true;
	}
	if (pos.y < -2 || pos.y >= (Game::gameY / Game::cellSize)) {
		return true;
	}
	//foreach collider
	for (auto& b : blockers) {
		if (b->posGrid.x >= pos.x && b->posGrid.x <= pos.x + 4 &&
			b->posGrid.y >= pos.y && b->posGrid.y <= pos.y + 2
			) {
			return true;
		}
	}

	return false;
}
bool World::UpdateCollisionEnemyDestroy(Vector2i pos) {
	for (auto& p : playerProj) {
		if (p->posGrid.x >= pos.x && p->posGrid.x <= pos.x + 4 &&
			p->posGrid.y >= pos.y && p->posGrid.y <= pos.y + 2
			) {
			playerProjToBeDeleted.push_back(p);
			return true;
		}
	}

	return false;
}

bool World::UpdateCollisionProjectile(Vector2i pos)
{
	return false;
}

void World::UpdateDeleted() {
	for (auto& d : enemiesToBeDeleted) {
		auto& e = world.enemies;
		auto pos = std::find(e.begin(), e.end(), d);
		if (pos != e.end())
			world.enemies.erase(pos);
	}

	for (auto& d : playerProjToBeDeleted) {
		auto& pp = world.playerProj;
		auto pos = std::find(pp.begin(), pp.end(), d);
		if (pos != pp.end()) {
			world.playerProj.erase(pos);
		}
	}

	//delete to be deleted list

	world.enemiesToBeDeleted.clear();
	world.playerProjToBeDeleted.clear();
}
