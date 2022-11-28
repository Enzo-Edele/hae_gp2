#pragma once

#include <vector>
#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "Lib.hpp"

using namespace sf;

class Line {
public:
	//tab contient point donné
	std::vector<sf::Vector2f> origins;
	//tab contient point baked
	std::vector<sf::Vector2f> baked;

	//bool dispaly control point
	bool displayControlPoints;

	//contructor
	Line() {
		baked.push_back(sf::Vector2f(10, 10));
		baked.push_back(sf::Vector2f(10, 110));
		baked.push_back(sf::Vector2f(110, 110));
		baked.push_back(sf::Vector2f(110, 10));
	}

	//translate      prend vector2f tr
	void Translate(Vector2f tr) {
		//foreach origins t    t += tr
		for (auto& t : origins) {
			t += tr;
		}
		//vec tab vec2f nu prend origins
		std::vector<Vector2f> nu = (origins);
		//setpoint nu
		SetPoint(nu);
	}

	//rebake
	void Rebake() {
		//vec tab vec2f nu prend origins
		std::vector<Vector2f> nu = (origins);
		//setpoint nu
		SetPoint(nu);
	}

	//Draw the line take window
	void Draw(RenderWindow& win) {
		//vertex array vb linestrip
		VertexArray vb(LineStrip);
		//foreach b baked
		for (auto& b : baked) {
			//color   A REVOIR
			sf::Color c;
			if (b.y < heightMap[0])
				c = colorMinMax[0];
			else if (b.y >= heightMap[1])
				c = colorMinMax[1];
			else {
				float t = (b.y - heightMap[0]) / (heightMap[1] - heightMap[0]);
				c = sf::Color(
					Lib::Lerp(colorMinMax[0].r, colorMinMax[1].r, t),
					Lib::Lerp(colorMinMax[0].g, colorMinMax[1].g, t),
					Lib::Lerp(colorMinMax[0].b, colorMinMax[1].b, t)
				);
			}

			//vertex vtx
			Vertex vtx(b, c);
			//vb append vtx
			vb.append(vtx);
		}

		//win draw vb
		win.draw(vb);

		//condition display control point
		if (displayControlPoints) {
			//foreach origins o
				// circleshape 8
				// origin
				// position o
				// color     0xFF4CE7ff
				// ouline color     0x8AFE2Bff
				// outlinethickness
				// draw shape
			for (auto& o : origins) {
				CircleShape shape(8);
				shape.setOrigin(8, 8);
				shape.setPosition(o);
				shape.setFillColor(Color(0xFF4CE7ff));
				shape.setOutlineColor(Color(0x8AFE2Bff));
				shape.setOutlineThickness(2);
				win.draw(shape);
			}
		}
	}

	//get point depending on idx
	sf::Vector2f Get(int idx) {
		//idx < 0
		if (idx < 0) idx = 0;
		//idx >= origin size
		if (idx >= origins.size()) idx = origins.size() - 1;
		//return origin at idx
		return origins[idx];
	}

	//tab vec de vector2f& en ref p, float tstep = 0.1f
	//set point
		//origins prend p
		//clear baked
		//int steps round 1.0 / tstep
		//double cstep = 0
		//for i 0 < size de p i++
			//set p0 a p3 de i - 1 a i + 2
			//cstep = 0.0
			//while cstep < 1.0
			//if cstep > 1.0 : cstep = 1
			//baked pushbacke (polynom p0 a p3 cstep)
			// cstep + tstep
			//if(cstep > 1.0 : break
	void SetPoint(std::vector<Vector2f>& p, float tstep = 0.1f) {
		origins = p;
		baked.clear();
		int step = std::round(1.0f / tstep);
		double cstep = 0;
		for (int i = 0; i < p.size(); i++) {
			auto p0 = Get(i - 1);
			auto p1 = Get(i);
			auto p2 = Get(i + 1);
			auto p3 = Get(i + 2);
			cstep = 0.0f;
			while (cstep < 1.0f) {
				if (cstep >= 1.0f) cstep = 1.0f;
				baked.push_back(Catmull::Polynom2(p0, p1, p2, p3, cstep));
				cstep += tstep;
				if (cstep > 1.0f) break;
			}
		}
	}

	Color colorMinMax[2] = { Color::White, Color::White };
	//heightmap en float de tab de 2 (150, 300)
	float heightMap[2] = { 100, 300 };
	
		// 0 1 => sur toute la  courbe
		// 0 n ( n = nombre de point
		// 2.5 
		// => interpoler entre 2 et 3 avec un t de 0.5
		//float globalT mul t par size de origin
		//int i converti en int globalT
		//float localT   gloabal t - i
		//p0 a p3 i - 1 a i + 2
		//return polynom2 p0 a p3 a localT
	Vector2f interpolateCatmull(float t){
		float globalT = t * origins.size();
		int i = (int)globalT;
		float localT = globalT - i;
		auto p0 = Get(i - 1);
		auto p1 = Get(i);
		auto p2 = Get(i + 1);
		auto p3 = Get(i + 2);
		return Catmull::Polynom2(p0, p1, p2, p3, localT);
	}

	Vector2f interpolateLinear(float t){
		float globalT = t * (baked.size() - 1);
		int i = (int)globalT;
		float localT = globalT - i;
		if (t >= 1.0f) return baked.back();
		if (localT <= 0) return baked[i];
		if (localT >= 1) return baked[i + 1];
		return Lib::Lerp(baked[i], baked[i + 1], localT);
	}
		// t compris 0 - 1 
		// 0 n nb point baked
		// interpole lineairement entre les deux pos bake avant et apres 
		//
		//float globalT          t mult taille de bakedcsize - 1
		//int i   int de globalT           //partie entiere entre 0 et n
		//float localT   gloabal t - i     // partie fractionnelle
		//if t >= 1 return back de baked
		//if localT <= 0 return baked i
		//if localT >= 1 return baked i + 1;
		//return lerp baked i, baked i + 1, local T
};