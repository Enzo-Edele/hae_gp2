#pragma once

#include "SFML/System/Vector2.hpp"
using namespace sf;

class Catmull {
public:
	//prend 5 double, 4 point et un t
	static inline double Polynom(double p0, double p1, double p2, double p3, double t) {
		double q = 2.0 * p1;
		double t2 = t * t;

		q += (-p0 + p2) * t;
		q += (2.0 * p0 - 5.0 * p1 + 4 * p2 - p3) * t2;
		q += (-p0 + 3 * p1 - 3 * p2 + p3) * t2 * t;

		return 0.5 * q;
	}


	//prend 4 vector2f et un double t
	static inline sf::Vector2f Polynom2(Vector2f p0, Vector2f p1, Vector2f p2, Vector2f p3, double t) {
		//return vector 2f avec polynom de x puis de y
		return Vector2f(Polynom(p0.x, p1.x, p2.x, p3.x, t), Polynom(p0.y, p1.y, p2.y, p3.y, t));
	}
};