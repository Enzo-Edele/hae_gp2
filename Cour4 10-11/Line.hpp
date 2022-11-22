#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "CatMull.hpp"
#include "Lib.hpp"

class Line {
public:
	std::vector<sf::Vector2f> origins;
	std::vector<sf::Vector2f> baked;
	bool enableControlPointsDisplay = false;

	Line() {
		baked.push_back(sf::Vector2f(200, 200));
		baked.push_back(sf::Vector2f(300, 250));
		baked.push_back(sf::Vector2f(400, 200));
		baked.push_back(sf::Vector2f(500, 200));
	}

	void Translate(sf::Vector2f tr) {
		for (auto& t : origins) {
			t += tr;
		}
		std::vector<sf::Vector2f> nu = (origins);
		SetPoint(nu);
	}

	void Rebake() {
		std::vector<sf::Vector2f> nu = (origins);
		SetPoint(nu);
	}

	void SetPoint(std::vector<sf::Vector2f> p, float tstep = 0.1f) { //tstep sert de resolution
		origins = p;
		baked.clear();
		double steps = std::ceil(1.0f / tstep);
		double cstep = 0.0;

		for (int i = 0; i < p.size(); i++) {
			auto p0 = get(i - 1);
			auto p1 = get(i);
			auto p2 = get(i + 1);
			auto p3 = get(i + 2);
			cstep = 0.0;
			//creer vertex interpolé
			while (cstep < 1.0f) {
				if (cstep >= 1.0f)
					cstep = 1.0f;
				baked.push_back(CatMull::Polynom2(p0, p1, p2, p3, cstep));
				cstep += tstep;
				if (cstep > 1.0f)
					break;
			}
		}
	}

	sf::Vector2f get(int idx) {
		if (idx < 0) idx = 0;
		if (idx >= origins.size()) idx = origins.size() - 1;
		return origins[idx];
	}

	void draw(sf::RenderWindow& win, sf::Color color = sf::Color::Cyan) {
		sf::VertexArray vb(sf::LineStrip);
		for (auto& b : baked) {
			sf::Vertex vtx(b, color);
			vb.append(vtx); //tous les vertex
		}

		win.draw(vb);

		if (enableControlPointsDisplay) {
			for (auto& b : origins) {
				sf::CircleShape ctrl(8);
				ctrl.setOrigin(8, 8);
				ctrl.setPosition(b);
				ctrl.setFillColor(sf::Color(0xFF4CE7ff));
				ctrl.setOutlineColor(sf::Color(0x8AFE2Bff));
				ctrl.setOutlineThickness(2);
				win.draw(ctrl);
			}
		}
	}

	sf::Vector2f InterpolateCatmull(float t) {
		float globalT = t * origins.size();

		int i = (int)globalT;
		float localT = globalT - i;
		auto p0 = get(i - 1);
		auto p1 = get(i);
		auto p2 = get(i + 1);
		auto p3 = get(i + 2);
		return CatMull::Polynom2(p0, p1, p2, p3, localT);
	}

	sf::Vector2f InterpolateLinear(float t) {
		float globalT = t * (baked.size() - 1);

		int i = (int)globalT;
		float localT = globalT - i;
		if (t >= 1.0f)
			return baked.back();
		if (localT <= 0) {
			return baked[i];
		}
		if (localT >= 1) {
			return baked[i + 1];
		}
		return Lib::Lerp(baked[i], baked[i + 1], localT);
	}
};