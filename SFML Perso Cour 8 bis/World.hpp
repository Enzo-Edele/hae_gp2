#pragma once

#include "Entity.hpp"

class World {
public:

	Entity* player;

	std::vector<Entity*> walls;

	std::vector<Cell*> validCells;
	std::vector<Cell*> pathCells;

	std::vector<VertexArray*> paths;

	void Update();

	bool UpdateCollision(float cx, float cy);

	void UpdateDeleted();

	void DrawValidCell(Vector2i bound);

	void DrawAllPath(Vector2i size);

	void DrawPath(std::vector<Cell*>);
};

extern World world;