#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class Lib {
public:
	static float Lerp(float a, float b, float t) {
		return a + (b - a) * t;
	}

	static sf::Vector2f Lerp(sf::Vector2f a, sf::Vector2f b, float t) {
		sf::Vector2f diff = b - a;
		diff.x *= t;
		diff.y *= t;
		return a + diff;
	}

	static int rand() {
		static bool isInit = false;
		if (!isInit) {
			clock_t now = clock();
			srand(now);
			isInit = true;
		}

		return ::rand();
	}

	static float randf() {
		return 1.0f * Lib::rand() / RAND_MAX;
	}
};