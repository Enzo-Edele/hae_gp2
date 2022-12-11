#include "State.hpp"

void Idle::ApplyState() {
	owner->sprite->setFillColor(Color::White);
}

void Idle::OnEvent(sf::Event& event) {
	if (event.type == Event::KeyReleased) {
		if (event.key.code == Keyboard::Up) {
			owner->dy -= 2.0f;
			owner->ChangeState(owner->jumpState);
		}
	}
}

void Idle::UpdateState() {

	Vector2f dir(0, 0);
	float speed = 0.05;
	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		dir.x--;
		owner->ChangeState(owner->walkState);
	}
	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		dir.x++;
		owner->ChangeState(owner->walkState);
	}

	float len = sqrt(dir.x * dir.x + dir.y * dir.y);
	if (len) {
		owner->dx += (dir.x / len) * speed;
		owner->dy += (dir.y / len) * speed;
	}

	if (owner->HasCollision(owner->cx + 2, owner->cy) || owner->HasCollision(owner->cx - 2, owner->cy) ||
		owner->HasCollision(owner->cx + 1, owner->cy) || owner->HasCollision(owner->cx - 1, owner->cy)) {
		owner->ChangeState(owner->coverState);
	}
}

void Cover::ApplyState() {
	owner->sprite->setFillColor(Color::Magenta);
}

void Cover::OnEvent(sf::Event& event) {
	if (event.type == Event::KeyReleased) {
		if (event.key.code == Keyboard::Up) {
			owner->dy -= 2.0f;
			owner->ChangeState(owner->jumpState);
		}
	}
}

void Cover::UpdateState() {
	Vector2f dir(0, 0);
	float speed = 0.05;
	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		dir.x--;
	}
	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		dir.x++;
	}

	float len = sqrt(dir.x * dir.x + dir.y * dir.y);
	if (len) {
		owner->dx += (dir.x / len) * speed;
		owner->dy += (dir.y / len) * speed;
	}

	if (!owner->HasCollision(owner->cx + 2, owner->cy) && !owner->HasCollision(owner->cx - 2, owner->cy) ||
		!owner->HasCollision(owner->cx + 1, owner->cy) && !owner->HasCollision(owner->cx - 1, owner->cy)) {
		owner->ChangeState(owner->idleState);
	}
}

void Walking::ApplyState() {
	owner->sprite->setFillColor(Color::Cyan);
}

void Walking::OnEvent(sf::Event& event) {
	if (event.type == Event::KeyReleased) {
		if (event.key.code == Keyboard::Up) {
			owner->dy -= 2.0f;
			owner->ChangeState(owner->jumpState);
		}
	}
}

void Walking::UpdateState() {
	Vector2f dir(0, 0);
	float speed = 0.05;
	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		dir.x--;
	}
	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		dir.x++;
	}

	float len = sqrt(dir.x * dir.x + dir.y * dir.y);
	if (len) {
		owner->dx += (dir.x / len) * speed;
		owner->dy += (dir.y / len) * speed;
	}

	//si owner walk plus mettre en idle
}

void Jumping::ApplyState() {
	owner->sprite->setFillColor(Color::Yellow);
}

void Jumping::OnEvent(sf::Event& event) {

}

void Jumping::UpdateState() {
	if (owner->dy > 0) {
		owner->ChangeState(owner->fallState);
	}
}

void Falling::ApplyState() {
	owner->sprite->setFillColor(Color::Green);
}

void Falling::OnEvent(sf::Event& event)
{
}

void Falling::UpdateState()
{
	if (owner->dy == 0) {
		owner->ChangeState(owner->fallState);
	}
}
