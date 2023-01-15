#include "Entity.hpp"

#include "Lib.hpp"
#include "World.hpp"

Entity::Entity(Vector2i pos, Vector2f shapeSize, Shape* shp) {
	shape = shp;
	posGrid = pos;
	size = shapeSize;
}

void Entity::SetCoordinateWtoG(Vector2f npos) {
	posWorld = npos;
	posGrid.x = (int)(posWorld.x / Game::cellSize);
	posGrid.y = (int)(posWorld.y / Game::cellSize);
	gridOffset.x = (posWorld.x - posGrid.x * Game::cellSize) / Game::cellSize;
	gridOffset.y = (posWorld.y - posGrid.y * Game::cellSize) / Game::cellSize;
}

void Entity::SetCoordinateGtoW(Vector2i npos) {
	posWorld.x = (npos.x + gridOffset.x) * Game::cellSize;
	posWorld.y = (npos.y + gridOffset.y) * Game::cellSize;
	SetCoordinateWtoG(posWorld);
}

bool Entity::HasCollision(Vector2i pos)
{
	if (world.UpdateCollisionPlayer(pos)) {
		return true;
	}

	return false;
}

void Entity::Update() {
	gridOffset += direction;
	direction *= 0.92f;

	while (gridOffset.x > 1) {
		if (HasCollision(Vector2i(posGrid.x + 1, posGrid.y))) {
			gridOffset.x = 0.9f;
			direction.x = 0;
		}
		else {
			gridOffset.x--;
			posGrid.x++;
		}
	}
	while (gridOffset.x < 0) {
		if (HasCollision(Vector2i(posGrid.x - 1, posGrid.y))) {
			gridOffset.x = 0.1f;
			direction.x = 0;
		}
		else {
			gridOffset.x++;
			posGrid.x--;
		}
	}
	while (gridOffset.y > 1) {
		if (HasCollision(Vector2i(posGrid.x, posGrid.y + 1))) {
			gridOffset.y = 0.9f;
			direction.y = 0;
		}
		else {
			gridOffset.y--;
			posGrid.y++;
		}
	}
	while (gridOffset.y < 0) {
		if (HasCollision(Vector2i(posGrid.x, posGrid.y - 1))) {
			gridOffset.y = 0.1f;
			direction.y = 0;
		}
		else {
			gridOffset.y++;
			posGrid.y--;
		}
	}

	//Sync
	posWorld = ((Vector2f)posGrid + gridOffset) * (float)Game::cellSize;
	shape->setPosition(posWorld);
	sprite.setPosition(posWorld);
}

void Entity::Move(Vector2f movDirection) {

}

Cell::Cell(Vector2i pos, Vector2f size, Shape* shp, Color color) : Entity(pos, size, shp) {
	shape->setFillColor(color);
	shape->setOutlineColor(Color::Black);

	Update();
}

Blocker::Blocker(Vector2i pos, Vector2f size, Shape* shp) : Entity(pos, size, shp) {
	shape->setFillColor(Game::colors[2]);
	shape->setOutlineColor(Color::Black);

	Update();
}

Player::Player(Vector2i pos, Vector2f size, Shape* shp, Texture newTexture) : Entity(pos, size, shp) {
	texture = newTexture;
	sprite.setTexture(texture);
	sprite.setPosition(Vector2f(posGrid.x * Game::cellSize, posGrid.y * Game::cellSize));
	offsetShoot = Vector2i(4, 1);

	if (!projectile.loadFromFile("Asset/Sprite/playerProj.png")) {
		printf("error can't load playerProj sprite");
	}
}

void Player::Update() {
	gridOffset += direction;
	direction *= 0.92f;

	while (gridOffset.x > 1) {
		if (HasCollision(Vector2i(posGrid.x + 1, posGrid.y))) {
			gridOffset.x = 0.9f;
			direction.x = 0;
		}
		else {
			gridOffset.x--;
			posGrid.x++;
		}
	}
	while (gridOffset.x < 0) {
		if (HasCollision(Vector2i(posGrid.x - 1, posGrid.y))) {
			gridOffset.x = 0.1f;
			direction.x = 0;
		}
		else {
			gridOffset.x++;
			posGrid.x--;
		}
	}
	while (gridOffset.y > 1) {
		if (HasCollision(Vector2i(posGrid.x, posGrid.y + 1))) {
			gridOffset.y = 0.9f;
			direction.y = 0;
		}
		else {
			gridOffset.y--;
			posGrid.y++;
		}
	}
	while (gridOffset.y < 0) {
		if (HasCollision(Vector2i(posGrid.x, posGrid.y - 1))) {
			gridOffset.y = 0.1f;
			direction.y = 0;
		}
		else {
			gridOffset.y++;
			posGrid.y--;
		}
	}
	if (world.UpdateCollisionPlayerDestroy(Vector2i(posGrid.x, posGrid.y))) {
		Killed();
	}

	//Sync
	posWorld = ((Vector2f)posGrid + gridOffset) * (float)Game::cellSize;
	shape->setPosition(posWorld);
	sprite.setPosition(posWorld);
}

void Player::Shoot() {
	world.playerProj.push_back(new Projectile((Vector2i)(posGrid + offsetShoot),
		Vector2f(8, 2),
		gridOffset,
		new RectangleShape(Vector2f(8, 2)),
		projectile));
}

void Player::Killed()
{
	SetCoordinateGtoW(Game::spawnPos[0]);
	Game::changeLives(-1);
}

Eneny::Eneny(Vector2i pos, Vector2f size, Shape* shp, Texture newTexture) : Entity(pos, size, shp) {
	texture = newTexture;
	sprite.setTexture(texture);
	sprite.setPosition(Vector2f(posGrid.x * Game::cellSize, posGrid.y * Game::cellSize));

	int rndPos = Lib::rand() % 3 + 1;
	posGrid = Game::spawnPos[rndPos];
}

void Eneny::Update() {
	direction = Vector2f(-0.4f, 0.0f);
	gridOffset += direction;
	direction *= 0.92f;

	while (gridOffset.x > 1) {
		if (HasCollision(Vector2i(posGrid.x + 1, posGrid.y))) {
			gridOffset.x = 0.9f;
			direction.x = 0;
		}
		else {
			gridOffset.x--;
			posGrid.x++;
		}
	}
	while (gridOffset.x < 0) {
		if (HasCollision(Vector2i(posGrid.x - 1, posGrid.y))) {
			gridOffset.x = 0.1f;
			direction.x = 0;
		}
		else {
			gridOffset.x++;
			posGrid.x--;
		}
	}
	while (gridOffset.y > 1) {
		if (HasCollision(Vector2i(posGrid.x, posGrid.y + 1))) {
			gridOffset.y = 0.9f;
			direction.y = 0;
		}
		else {
			gridOffset.y--;
			posGrid.y++;
		}
	}
	while (gridOffset.y < 0) {
		if (HasCollision(Vector2i(posGrid.x, posGrid.y - 1))) {
			gridOffset.y = 0.1f;
			direction.y = 0;
		}
		else {
			gridOffset.y++;
			posGrid.y--;
		}
	}
	if (world.UpdateCollisionEnemyDestroy(Vector2i(posGrid.x, posGrid.y))) {
		world.enemiesToBeDeleted.push_back(this);
		Game::changeScore(50);
	}

	//Sync
	posWorld = ((Vector2f)posGrid + gridOffset) * (float)Game::cellSize;
	shape->setPosition(posWorld);
	sprite.setPosition(posWorld);
}

bool Eneny::HasCollision(Vector2i pos) {
	if (world.UpdateCollisionEnemy(pos)) {
		return true;
	}

	return false;
}

void Eneny::Shoot() {

}

Projectile::Projectile(Vector2i pos, Vector2f size, Vector2f offset, Shape* shp, Texture newTexture) : Entity(pos, size, shp) {
	texture = newTexture;

	gridOffset = offset;

	sprite.setTexture(texture);
	sprite.setPosition(Vector2f(pos.x * Game::cellSize, pos.y * Game::cellSize));
}

//hasCollision ???

bool Projectile::HasCollision(Vector2i pos) {
	if (world.UpdateCollisionProjectile(pos)) {
		return true;
	}

	return false;
}

void Projectile::Update() {
	direction = Vector2f(1.0f, 0.0f);
	gridOffset += direction;
	direction *= 0.92f;

	while (gridOffset.x > 1) {
		if (HasCollision(Vector2i(posGrid.x + 1, posGrid.y))) {
			gridOffset.x = 0.9f;
			direction.x = 0;
		}
		else {
			gridOffset.x--;
			posGrid.x++;
		}
	}
	while (gridOffset.x < 0) {
		if (HasCollision(Vector2i(posGrid.x - 1, posGrid.y))) {
			gridOffset.x = 0.1f;
			direction.x = 0;
		}
		else {
			gridOffset.x++;
			posGrid.x--;
		}
	}
	while (gridOffset.y > 1) {
		if (HasCollision(Vector2i(posGrid.x, posGrid.y + 1))) {
			gridOffset.y = 0.9f;
			direction.y = 0;
		}
		else {
			gridOffset.y--;
			posGrid.y++;
		}
	}
	while (gridOffset.y < 0) {
		if (HasCollision(Vector2i(posGrid.x, posGrid.y - 1))) {
			gridOffset.y = 0.1f;
			direction.y = 0;
		}
		else {
			gridOffset.y++;
			posGrid.y--;
		}
	}

	//Sync
	posWorld = ((Vector2f)posGrid + gridOffset) * (float)Game::cellSize;
	shape->setPosition(posWorld);
	sprite.setPosition(posWorld);
}
