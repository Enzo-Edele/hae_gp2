#pragma once

class Lib {
public:
	static void Memcpy(char* dest, const char* src, int size) {
		for (int i = 0; i < size; i++)
		{
			dest[i] = src[i];
		}
	}

	static const char* StrChr(const char* grange, char chat)
	{
		char *ptr = new char[512];
		while (*grange)
		{
			if (*grange == chat)
			{
				int idx = 0;
				while (*grange)
				{
					ptr[idx] = *grange;
					*grange++;
					idx++;
				}
				//printf(*ptr, "\n");
				return ptr; //cast marche pas
			}
			grange++;
		}
		return nullptr;
	};

	static char* StrStr(char* meuleDeFoin, char* aiguille) {
		char* ptr = new char[512];
		char* limite = meuleDeFoin;
		limite += strlen(aiguille);
		while (*limite)
		{
			if (compareStr(meuleDeFoin, aiguille))
			{
				int idx = 0;
				while (*meuleDeFoin)
				{
					ptr[idx] = *meuleDeFoin;
					*meuleDeFoin++;
					idx++;
				}
				//printf(*ptr);
				return ptr; //return marche pas
			}
			limite++;
			meuleDeFoin++;
		}
		return nullptr;
	};

	static bool compareStr(char* tested, char* src) {
		bool test = true;
		for (int i = 0; i < strlen(src); i++)
		{
			if (test && *tested != *src) {
				test = false;
			}
			*tested++;
			*src++;
		}
		return test;
	}
};