#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "CatMull.hpp"

class Line {
public:
	std::vector<sf::Vector2f> baked;

	Line() {
		baked.push_back(sf::Vector2f(200, 200));
		baked.push_back(sf::Vector2f(300, 250));
		baked.push_back(sf::Vector2f(400, 200));
		baked.push_back(sf::Vector2f(500, 200));
	}

	void SetPoint(std::vector<sf::Vector2f> p, float tstep = 0.1f) { //tstep sert de resolution
		auto get = [&p](int idx) {
			if (idx < 0) idx = 0;
			if (idx >= p.size()) idx = p.size() - 1;
			return p[idx];
		};
		baked.clear();
		double steps = std::ceil(1.0f / tstep);
		double cstep = 0.0;

		sf::VertexArray toDraw(sf::PrimitiveType::Lines);

		for (int i = 0; i < p.size() - 1; i++) {
			auto p0 = get(i - 1);
			auto p1 = get(i);
			auto p2 = get(i + 1);
			auto p3 = get(i + 2);
			cstep = 0.0;
			//creer vertex interpolé
			for (int i = 0; i < steps; i++) {
				baked.push_back(CatMull::Polynom2(p0, p1, p2, p3, cstep));
				cstep += tstep;
			}
		}
	}

	void draw(sf::RenderWindow& win) {
		sf::VertexArray vb(sf::LineStrip);
		for (auto& b : baked) {
			sf::Vertex vtx(b, sf::Color::Cyan);
			vb.append(vtx); //tous les vertex
		}
		win.draw(vb);
	}
};