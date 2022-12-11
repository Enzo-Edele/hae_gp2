#pragma once

#include <string>
#include <vector>
#include<sys/stat.h>

#include <SFML/Graphics.hpp>

#include "Entity.hpp"
#include "World.hpp"

class LevelFile {
public:
	static std::vector<Entity> Load(std::string path) {
		std::vector<Entity> brick;

		FILE* file = nullptr;
		fopen_s(&file, path.c_str(), "r");
		if (!file) {
			return brick;
		}

		Vector2f pos;
		int nbCmd = 0;

		do {
			nbCmd = fscanf_s(file, "%i %i\n", pos.x, pos.y);
			if (nbCmd > 0)
				brick.push_back(Wall(pos));
		} while (nbCmd > 0);

		fclose(file);

		return brick;
	}
	
	static bool Save(std::string path, std::vector<Entity>& data) {
		FILE* file = nullptr;
		fopen_s(&file, path.c_str(), "w");
		if (!file) {
			return false;
		}
		for (auto& d : data) {
			fprintf(file, "%f %f\n", d.xx, d.yy);
		}
		fflush(file);
		fclose(file);

		return true;
	}
};