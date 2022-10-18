#pragma once

class Lib {
public:
	static void MemCpy(char* dest, const char* src, int size) {
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

	static char* StrStr(char* meuleDeFoin, char* aiguille) { //marche aussi pour le string tree prefixe et patern
		while (*meuleDeFoin && !compareStr(meuleDeFoin, aiguille))
		{
			meuleDeFoin++;
		}
		if(!meuleDeFoin)
			return nullptr;

		return meuleDeFoin;
	};

	static bool compareStrPrefixeCorrection(const char* src, const char* tok)
	{
		while (*tok) { //on peut faire un index peut de différence
			if (*tok != *src)
				return false;
			else {
				*tok++;
				*src++;
			}
		}
		return true;
	}

	static bool compareStr(char* tested, char* src) {
		bool test = true;
		int size = strlen(src); //mettre en cache dans int le strlen(src) pour éviter de trop l'appeller
		for (int i = 0; i < size; i++) 
		{
			if (test && *tested != *src) {
				test = false;
			}
			*tested++;
			*src++;
		}
		return test;
	}
	//P(0) -> P(1)
	//P(n) -> P(n + 1)
	//
	static void MemCpyRec(char* dest, const char* src, int size) {
		//cas initial
		if (size == 0)
			return;
		//cas recurrent
		*dest = *src;
		MemCpyRec(dest + 1, src + 1, size - 1);
		//combine

		//
		return;
	}

	static const char* StrChrRec(const char* src, char c)
	{
		if (*src == c)
			return src;
		if (src && *src != c) {
			*src++;
			StrChrRec(src, c);
		}
		else
			return nullptr;
	};

	static char* StrStrRec(char* meuleDeFoin, char* aiguille) { //marche aussi pour le string tree prefixe et patern
		if(compareStr(meuleDeFoin, aiguille))
			return meuleDeFoin;
		if (*meuleDeFoin && !compareStr(meuleDeFoin, aiguille))
		{
			meuleDeFoin++;
			StrStrRec(meuleDeFoin, aiguille);
		}
		else
			return nullptr;
	};
};