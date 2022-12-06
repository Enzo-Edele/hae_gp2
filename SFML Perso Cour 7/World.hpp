#pragma once

class World {
public:

	void Update();

	void UpdateCollision();

	void UpdateDeleted();
};

extern World world;