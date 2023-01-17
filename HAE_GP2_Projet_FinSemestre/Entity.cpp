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

	if (!boom0.loadFromFile("Asset/Sprite/boom0.png")) {
		printf("error can't load boom0 sprite");
	}
	if (!boom1.loadFromFile("Asset/Sprite/boom1.png")) {
		printf("error can't load boom1 sprite");
	}
	if (!boom2.loadFromFile("Asset/Sprite/boom2.png")) {
		printf("error can't load boom2 sprite");
	}
	if (!boom3.loadFromFile("Asset/Sprite/boom3.png")) {
		printf("error can't load boom3 sprite");
	}

	sprite.setTexture(boom0);

	lifespawn = 0.6f;

	Update();
}

void Cell::Lifespawn(float dt) {
	if (lifespawn > 0) {
		lifespawn -= dt;
	}
	else {
		world.cellsToBeDeleted.push_back(this);
	}
	if (lifespawn < 0.15f)
		sprite.setTexture(boom3);
	else if (lifespawn < 0.30f)
		sprite.setTexture(boom2);
	else if (lifespawn < 0.45f)
		sprite.setTexture(boom1);
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

	invincibleTimer = 0.0f;

	if (!projectile.loadFromFile("Asset/Sprite/playerProj.png")) {
		printf("error can't load playerProj sprite");
	}
}

void Player::Update(float dt) {
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

	if (invincibleTimer > 0) {
		invincibleTimer -= dt;
	}
	else if (invincibleTimer != 0) {
		invincibleTimer = 0;
	}

	if (shotTimer > 0) {
		shotTimer -= dt;
	}
	else if (shotTimer != 0) {
		shotTimer = 0;
	}
}

void Player::Shoot() {
	if (shotTimer == 0) {
		world.playerProj.push_back(new Projectile((Vector2i)(posGrid + offsetShoot),
			Vector2f(12, 4),
			gridOffset,
			new RectangleShape(Vector2f(12, 4)),
			projectile,
			Vector2f(1.0f, 0.0f),
			ProjectileType::laser));
		shotTimer = 0.5f;
	}
}

void Player::Killed()
{
	if (invincibleTimer == 0 && Game::state == GameState::Game) {
		world.cells.push_back(new Cell(Vector2i(posGrid.x + 2, posGrid.y + 1),
			Vector2f(Game::cellSize, Game::cellSize),
			new RectangleShape(Vector2f(Game::cellSize, Game::cellSize)),
			Color::Blue));

		SetCoordinateGtoW(Game::spawnPos[0]);
		Game::changeLives(-1);
		invincibleTimer = 3.0f;

		if (Game::lives < 0) {
			Game::EndGame();
			//world.Clear();
			direction = Vector2f(0, 0);
			SetCoordinateGtoW(Game::spawnPos[0]);
		}
	}
}
//add ennemy type
Eneny::Eneny(Vector2i pos, Vector2f size, Shape* shp, Texture newTexture, EnemyType nType) : Entity(pos, size, shp) {
	texture = newTexture;
	sprite.setTexture(texture);
	sprite.setPosition(Vector2f(posGrid.x * Game::cellSize, posGrid.y * Game::cellSize));
	offsetShoot = Vector2i(0, 1);

	type = nType;

	if (type == EnemyType::corvette) {
		posGrid = Vector2i(80, Lib::rand() % 35 + 6);
	}
	else if (type == EnemyType::cruiser) {
		int rndPos = Lib::rand() % 5 + 1;
		if (rndPos < 4)
			posGrid = Game::spawnPos[rndPos];
		else
			posGrid = Vector2i(80, Lib::rand() % 25 + 11);
	}
	if (type == EnemyType::missileCorvette) {
		posGrid = Vector2i(60, Lib::rand() % 35 + 6);
	}

	shootDirections.push_back(Vector2f(-1.0f, 0.0f));
	shootDirections.push_back(Vector2f(-0.7f, 0.3f));
	shootDirections.push_back(Vector2f(-0.7f, -0.3f));

	if (!projectile.loadFromFile("Asset/Sprite/enemyProj.png")) {
		printf("error can't load playerProj sprite");
	}
	if (!missile.loadFromFile("Asset/Sprite/enemyMissile.png")) {
		printf("error can't load enemyMissile sprite");
	}
}

void Eneny::Update(float dt) {
	if (type == EnemyType::cruiser) {
		direction = Vector2f(-0.2f, 0.0f);
	}
	if (type == EnemyType::corvette) {
		direction = Vector2f(-0.2f, 0.0f);
	}
	if (type == EnemyType::missileCorvette) {
		direction = Vector2f(0.0f, 0.0f);
	}
	gridOffset += direction;
	//direction *= 0.92f;

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
		if (type == EnemyType::cruiser) {
			world.cells.push_back(new Cell(Vector2i(posGrid.x + 2, posGrid.y + 1),
				Vector2f(Game::cellSize, Game::cellSize),
				new RectangleShape(Vector2f(Game::cellSize, Game::cellSize)),
				Color::Blue));
		}
		else if (type == EnemyType::corvette) {
			world.cells.push_back(new Cell(Vector2i(posGrid.x + 1, posGrid.y + 1),
				Vector2f(Game::cellSize, Game::cellSize),
				new RectangleShape(Vector2f(Game::cellSize, Game::cellSize)),
				Color::Blue));
		}
		else if (type == EnemyType::missileCorvette) {

		}
		Game::changeScore(50);
	}

	//Sync
	posWorld = ((Vector2f)posGrid + gridOffset) * (float)Game::cellSize;
	shape->setPosition(posWorld);
	sprite.setPosition(posWorld);

	if (shotTimer > 0) {
		shotTimer -= dt;
	}
	else {
		if (type == EnemyType::corvette) {
			shotTimer = Lib::rand() % 1 + 3;
			Shoot();
		}
		if (type == EnemyType::cruiser) {
			shotTimer = Lib::rand() % 2 + 5;
			ShootSpe();
		}
		if (type == EnemyType::missileCorvette) {
			shotTimer = Lib::rand() % 1 + 3;
			Shoot();
		}
	}
}

bool Eneny::HasCollision(Vector2i pos) {
	if (world.UpdateCollisionEnemy(pos)) {
		return true;
	}

	return false;
}

void Eneny::Shoot() {
	if (type == EnemyType::corvette) {
		world.enemyProj.push_back(new Projectile((Vector2i)(posGrid + offsetShoot),
			Vector2f(12, 4),
			gridOffset,
			new RectangleShape(Vector2f(12, 4)),
			projectile,
			Vector2f(-1.0f, 0.0f),
			ProjectileType::laser));
	}
	if (type == EnemyType::missileCorvette) {
		world.enemyProj.push_back(new Projectile((Vector2i)(posGrid + offsetShoot),
			Vector2f(16, 8),
			Vector2f(2.0f, 1.0f),
			new RectangleShape(Vector2f(16, 8)),
			missile,
			Vector2f(-1.0f, 0.0f),
			ProjectileType::missile));
		world.enemyProj.push_back(new Projectile((Vector2i)(posGrid + offsetShoot),
			Vector2f(16, 8),
			Vector2f(2.0f, -3.0f),
			new RectangleShape(Vector2f(16, 8)),
			missile,
			Vector2f(-1.0f, 0.0f),
			ProjectileType::missile));
	}
}

void Eneny::ShootSpe()
{
	for (int i = 0; i < shootDirections.size(); i++) {
		world.enemyProj.push_back(new Projectile((Vector2i)(posGrid + offsetShoot),
			Vector2f(12, 4),
			gridOffset,
			new RectangleShape(Vector2f(12, 4)),
			projectile,
			shootDirections[i],
			ProjectileType::laser));
	}
}

Projectile::Projectile(Vector2i pos, Vector2f size, Vector2f offset, Shape* shp, Texture newTexture, Vector2f dir, ProjectileType nType) : Entity(pos, size, shp) {
	texture = newTexture;

	gridOffset = offset;
	direction = dir;

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

void Projectile::Forward(int px)
{
	trs = trs.translate(Vector2f(0, -px));
	sprite.setPosition(trs.transformPoint(0, 0));

	shape->setFillColor(Color::Transparent);
}

void Projectile::Update() {
	gridOffset += direction;
	//direction *= 0.92f;

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
