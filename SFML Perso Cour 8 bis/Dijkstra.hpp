#pragma once

#include <iostream>
#include <string>

#include <unordered_map>
#include<algorithm>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Entity.hpp"
#include "World.hpp"

using namespace sf;

namespace std {
	template <> struct hash<sf::Vector2i> {
		inline std::size_t operator()(const Vector2i& k) const {
			using std::hash;
			return std::size_t((k.y * 16 * 1024) + k.x);
		};
	};
}

typedef std::unordered_map<Vector2i, Vector2i> AssocGraph;

class Dijkstra {
public:
	AssocGraph predecessor;

	std::vector<Cell*> validCellDijkstra;
	Cell* start;
	//pred

	Dijkstra(std::vector<Cell*>& graph) {
		validCellDijkstra = graph;
	}

	Cell* findCell(Vector2i startPos) {
		for (int i = 0; i < validCellDijkstra.size(); i++) {
			if (validCellDijkstra[i]->cx == startPos.x && validCellDijkstra[i]->cy == startPos.y) {
				return validCellDijkstra[i];
			}
		}
		std::cout << "not find";
		return new Cell(Vector2f(-1, -1));
	}

	void Init(Vector2i startPos) {
		start = findCell(startPos);
		for (auto& v : validCellDijkstra) {
			v->weight = 2500;
		}
		start->weight = 0;
	}

	int findMin(std::vector<sf::Vector2i> q) {
		int mini = 9999;
		int sommet = -1;
		for (int i = 0; i < q.size(); i++) {
			if (findCell(q[i])->weight < mini) {
				mini = findCell(q[i])->weight;
				sommet = i;
			}
		}
		return sommet;
	}

	void UpdateDistance(Vector2i s1, Vector2i s2) {
		float ndist = findCell(s1)->weight + Heuristic(s1, s2);
		if (findCell(s2)->weight > ndist) {
			findCell(s2)->weight = findCell(s1)->weight + Heuristic(s1, s2);
			predecessor[s2] = s1;
		}
	}

	float Heuristic(Vector2i s1, Vector2i s2) {
		float dx = s2.x - s1.x;
		float dy = s2.y - s1.y;
		return sqrt(dx * dx + dy * dy);
	}

	std::vector<Cell*> FindNeighbor(Vector2i pos){
		std::vector<Cell*> neighborList;
		neighborList.push_back(findCell(Vector2i(pos.x + 1, pos.y)));
		neighborList.push_back(findCell(Vector2i(pos.x - 1, pos.y)));
		neighborList.push_back(findCell(Vector2i(pos.x, pos.y + 1)));
		neighborList.push_back(findCell(Vector2i(pos.x, pos.y - 1)));

		return neighborList;
	}

	void build(Vector2i startPos) {
		Init(startPos);
		std::vector<sf::Vector2i> q;
		for (auto& v : validCellDijkstra) {
			q.push_back(Vector2i(v->cx, v->cy));
		}

		while(!q.empty()){
			int s1Idx = findMin(q);
			if (s1Idx == -1) break;

			Vector2i s1 = q[s1Idx];
			q.erase(q.begin() + s1Idx);
			
			std::vector<Cell*> s1Neighbor = FindNeighbor(Vector2i(s1.x, s1.y));

			for (int i = 0; i < s1Neighbor.size(); i++) {
				Cell* test = findCell(Vector2i(s1Neighbor[i]->cx, s1Neighbor[i]->cy));
				if(test->cx != -1)
					UpdateDistance(s1, Vector2i(s1Neighbor[i]->cx, s1Neighbor[i]->cy));
			}
		}
	}

	void DrawAllPath(Vector2i size)
	{
		//world.paths.clear();
		
		Vector2i temp;

		for (int y = 0; y < size.y; y++) {
			VertexArray* path = new VertexArray(LinesStrip);
			for (int x = 0; x < size.x; x++) {
				temp = predecessor[Vector2i(x, y)];
				path->append(Vertex(Vector2f(temp.x * Game::cellSize + 8, temp.y * Game::cellSize + 8), Color::Green));
			}
			world.paths.push_back(path);
			//path.clear();
		}
	}

	void DrawPath(Vector2i destination) {
		std::vector<Cell*> toDraw;
		Vector2i temp;

		temp = predecessor[destination];
		toDraw.push_back(findCell(destination));
		int idx = 0;

		bool destReach = false;

		while (temp != Vector2i(start->cx, start->cy) && idx < 500) {
			toDraw.push_back(findCell(temp));
			temp = predecessor[temp];
			idx++;
			if (temp == destination) destReach = true;
		}
		world.pathCells.clear();
		if (destReach) {

		}
		world.DrawPath(toDraw);
	}


	void SetPath(Player* player, Vector2i destination) {
		std::vector<Cell*> bestPath;
		std::vector<Cell*> bestPathOrdered;

		Vector2i temp;
		temp = predecessor[destination];
		bestPath.push_back(findCell(destination));
		int idx = 0;
		while (temp != Vector2i(start->cx, start->cy) && idx < 500) {
			bestPath.push_back(findCell(temp));
			temp = predecessor[temp];
			idx++;
		}
		for (int i = bestPath.size() - 1; i >= 0; i--) {
			bestPathOrdered.push_back(bestPath[i]);
		}
		player->path = bestPathOrdered;
	}
};