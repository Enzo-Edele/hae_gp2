#pragma once

#include <string>
#include <vector>
#include <sys/stat.h>

#include "Comande.hpp"

//std format sera remplacant printf scanf

class CommandeFile {
public:
	static std::vector<Cmd> Load(std::string path) {
		std::vector<Cmd> cmd;

		FILE* file = nullptr;
		fopen_s(&file, path.c_str(), "r");
		if (!file) {
			return cmd;
		}

		CmdId id = CmdId::Reset;
		double data = 0;
		int nbCmd = 0;

		do {
			nbCmd = fscanf_s(file, "%d %f\n", &id, &data);
			if(nbCmd > 0)
				cmd.push_back(Cmd(id, data));
		} while (nbCmd > 0);

		fclose(file);

		return cmd;
	}

	static bool Save(std::string path, std::vector<Cmd>& data) {
		FILE* file = nullptr;
		fopen_s(&file, path.c_str(), "w");
		if (!file) {
			return false;
		}
		for (auto& d : data) {
			fprintf(file, "%d %f\n", d.id, d.data);
		}
		fflush(file);
		fclose(file);

		return true;
	}

	static std::vector<Cmd> LoadScript(std::string path) {
		std::vector<Cmd> cmd;

		FILE* file = nullptr;
		fopen_s(&file, path.c_str(), "r");
		if (!file) {
			return cmd;
		}

		int nbCmd = 0;

		char comandeName[128] = {};

		do {
			Cmd c(CmdId::Advance, 0.0);
			comandeName[0] = 0;
			nbCmd = fscanf_s(file, "%s %f\n", comandeName, &c.data);

			if (0 == strcmp(comandeName, "Advance")) c.id = CmdId::Advance;
			if (0 == strcmp(comandeName, "RotateLeft")) c.id = CmdId::RotateLeft;
			if (0 == strcmp(comandeName, "RotateRight")) c.id = CmdId::RotateRight;
			if (0 == strcmp(comandeName, "Reset")) c.id = CmdId::Reset;
			if (0 == strcmp(comandeName, "PenChange")) c.id = CmdId::PenChange;

			if (nbCmd > 0)
				cmd.push_back(c);
		} while (nbCmd > 0);

		fclose(file);

		return cmd;
	}

	static bool SaveScript(std::string path, std::vector<Cmd>& data) {
		FILE* file = nullptr;
		fopen_s(&file, path.c_str(), "w");
		if (!file) {
			return false;
		}
		for (auto& d : data) {
			switch (d.id) {
			case CmdId::Advance: fprintf(file, "Advance %lf\n", d.data); break;
			case CmdId::RotateLeft: fprintf(file, "RotateLeft %lf\n", d.data); break;
			case CmdId::RotateRight: fprintf(file, "RotateRight %lf\n", d.data); break;
			case CmdId::Reset: fprintf(file, "Reset %lf\n", d.data); break;
			case CmdId::PenChange: fprintf(file, "PenChange %lf\n", d.data); break;
			default: 
				break;
			}
		}
		fflush(file);
		fclose(file);

		return true;
	}

};