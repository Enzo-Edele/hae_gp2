#pragma once

class Lib {
public:
	static void Memcpy(char* dest, const char* src, int size) {
		for (int i = 0; i < size; i++)
		{
			dest[i] = src[i];
		}
	}

	static const char* StrChr(const char* src, char c)
	{
		while (*src && *src != c)
		{
			src++;
		}
		if(!src)
			return nullptr;

		return src;
	};

	static char* StrStr(char* meuleDeFoin, char* aiguille) {
		while (*meuleDeFoin && !compareStr(meuleDeFoin, aiguille))
		{
			meuleDeFoin++;
		}
		if(!meuleDeFoin)
			return nullptr;

		return meuleDeFoin;
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

	static void MemcpyRec(char* dest, const char* src, int size, int idx = 0) {
		if (idx < size) {
			dest[idx] = src[idx];
			src++;
			dest++;
			idx++;
			MemcpyRec(dest, src, size, idx);
		}
	}
};