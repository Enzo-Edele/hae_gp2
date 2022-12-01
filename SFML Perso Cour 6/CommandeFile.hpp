#pragma once

#include <string>
#include <vector>

#include "Comande.hpp"

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
		//return nullptr si null
		//sinon lis
		//renvoie objet cmd file
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
		//ouvrir en écriture
		//sauv commande avec printf
		//flusher le fichier
		//fermer
		//renvouyer true / falser
	}
};