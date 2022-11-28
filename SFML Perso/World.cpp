#include "World.hpp"

#include <SFML/Audio.hpp>
#include <iostream>

void World::Update() {
	for (auto& b : bonuses) {
		b->Update();
	}

	UpdateCollision();
	UpdateDeleted();
}

void World::UpdateCollision() {
	for (auto& b : balls) {
		if (!b->hooked) {
			int nbColls = 0;
			Entity* collider = nullptr;

			auto bb = b->getGlobalBounds();
			for (auto& s : statics) {
				if (s->getGlobalBounds().intersects(bb)) {
					collider = s;
					nbColls++;
					//s->Hit();
				}
			}
			if (nbColls >= 2) {
				b->setPosition(b->lastPos);
				b->speed.x = -b->speed.x;
				b->speed.y = -b->speed.y;
				collider->Hit();
			}
			else if (nbColls >= 1) {
				Pad* isPad = dynamic_cast<Pad*>(collider);
				if (isPad)
				{
					if (b->getPosition().x < isPad->getPosition().x && (b->speed.x > 0))
						b->speed.x = -b->speed.x;
					else if (b->getPosition().x > isPad->getPosition().x && (b->speed.x < 0))
						b->speed.x = -b->speed.x;
					b->speed.y = -b->speed.y;
				}
				else
				{
					auto sb = collider->getGlobalBounds();
					sf::FloatRect lineUp(sf::Vector2f(sb.left, sb.top), sf::Vector2f(sb.width, 1));
					sf::FloatRect lineDown(sf::Vector2f(sb.left, sb.top + sb.height), sf::Vector2f(sb.width, 1));
					sf::FloatRect lineLeft(sf::Vector2f(sb.left, sb.top), sf::Vector2f(1, sb.height));
					sf::FloatRect lineRight(sf::Vector2f(sb.left + sb.width, sb.top), sf::Vector2f(1, sb.height));

					if (bb.intersects(lineUp) || bb.intersects(lineDown))
						b->speed.y = -b->speed.y;

					if (bb.intersects(lineLeft) || bb.intersects(lineRight))
						b->speed.x = -b->speed.x;
					collider->Hit();
				}
			}
			else {

			}
		}
	}

	//checker collision entre pad et bonus
	for (auto& p : pads) {
		Entity* collider = nullptr;

		auto pb = p->getGlobalBounds();
		for (auto& b : bonuses) {
			if (b->getGlobalBounds().intersects(pb)) {
				collider = b;
				p->Hit(b->type);
					// -> utiliser un int et un switch OU avoir différent bonus
				world.bonusDeleted.push_back(b);
			}
		}
	}
}

void World::UpdateDeleted() {
	for (auto& d : toBeDeleted) {
		auto& ws = world.statics;
		auto pos = std::find(ws.begin(), ws.end(), d);
		if (pos != ws.end())
			world.statics.erase(pos);
	}

	for (auto& d : bonusDeleted) {
		auto& wb = world.bonuses;
		auto pos = std::find(wb.begin(), wb.end(), d);
		if (pos != wb.end()) {
			world.bonuses.erase(pos);
		}
	}
	//make a ref
	world.toBeDeleted.clear();
	//delete ref
}
