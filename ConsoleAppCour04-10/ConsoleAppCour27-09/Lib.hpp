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

		//on retourne
		return;
	}

	static const char* StrChrRec(const char* src, char c)
	{
		//cas initial
		if (!*src)
			return nullptr;
		//cas recurrent
		if (*src == c) {
			return src;
		}
		return StrChrRec(src + 1, c);
		//combine

		//
	};

	static bool StrStrRecPref(const char* src, const char* c) {

	}

	static char* StrStrRec(char* meuleDeFoin, char* aiguille) { //marche aussi pour le string tree prefixe et patern
		//cas initial
		if (meuleDeFoin == nullptr) {
			return nullptr;
		}
		if(*meuleDeFoin == 0) {
			return *aiguille ? meuleDeFoin : nullptr;
		}
		//cas recurrent
		if (compareStr(meuleDeFoin, aiguille)) {
			return meuleDeFoin;
		}
		return StrStrRec(meuleDeFoin + 1, aiguille);
	};

	static int StrlenRec(const char* str) { //check 
		if (!*str)
			return 0;
		else
		{
			str++;
			return 1 + StrlenRec(str);
		}
	}

	static void StrCpyRec(char* dest, const char* src) {
		if (!*src){
			return;
		}
		if(*src )
		{
			*dest = *src;
			StrCpyRec(dest + 1, src + 1);
		}
	}

	static void StrnCpyRec(char* dest, const char* src, int charMaxCpy) {
		if (!*src) {
			return;
		}
		if (charMaxCpy == 0)
			return;
		if (*src)
		{
			*dest = *src;
			StrnCpyRec(dest + 1, src + 1, charMaxCpy -1);
		}
	}

	static void ZeroMemory(char* dest, int nbBytes) {
		if (nbBytes <= 0) return;
		if (!dest) return;

		*dest = 0;
		ZeroMemory(dest + 1, nbBytes - 1);
	}
	static int StrCmp(const char* str1, const char* str2) {
		if (!*str1 && !*str2)
			return 0;
		if (!*str1)
			return -1;
		if (!*str2)
			return 1;
		if (*str1 < *str2)
			return -1;
		if (*str1 > *str2)
			return 1;

		return StrCmp(str1 + 1, str2 + 1);
	}
};