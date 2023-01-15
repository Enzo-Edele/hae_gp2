#pragma once

#include <chrono>
#include <ctime>
#include <cstdlib>
#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/Color.hpp"

using namespace sf;

class Lib {
public:
	static int rand() {
		static bool isInit = false;
		if (!isInit) {
			clock_t now = clock();
			srand(now);
			isInit = true;
		}
		return ::rand();
	}

	static float randF() {
		return 1.0f * Lib::rand() / RAND_MAX;
	}

	static float Lerp(float a, float b, float t) {
		return a + (b - a) * t;
	};

	static sf::Vector2f Lerp(sf::Vector2f a, sf::Vector2f b, float t) {
		sf::Vector2f diff = b - a;
		diff.x *= t;
		diff.y *= t;
		return a + diff;
	};

	static double getTimestamp() {
		std::chrono::nanoseconds ns =
			std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch());
		return ns.count() / 1000000000.0;
	};

	static bool safeNormalize(Vector2f & inOut) {
		float distSq = inOut.x * inOut.x + inOut.y * inOut.y;
		if(distSq){
			float dist = sqrt(distSq);
			inOut.x /= dist;
			inOut.y /= dist;
			return true;
		}
		return false;
	}
};