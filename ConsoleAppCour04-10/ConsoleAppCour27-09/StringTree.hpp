#pragma once

#include <string>

class StringTree {
public:
	char* str;

	StringTree* left = nullptr;
	StringTree* right = nullptr;

	StringTree* insert(char* val);
	StringTree* remove(char* val);
	void print();

	void findstring(char* strscr);
	void findprfstring(char* prf);

	int compareString(char* tested, char* src);

	int compareStringSame(char* tested, char* src);

	~StringTree() 
	{
		//printf("Leaf Delete, \n");
	}
};

class StringTreeControler {
public:
	StringTree* root = nullptr;

	void insert(char* str) {
		if (!root) {
			root = new StringTree();
			root->str = str;
		}
		else
			root->insert(str);
	}

	void remove(char* str) {
		//printf("Start remove : \n");
		root = root->remove(str);
	}

	void print() {
		if (root)
			root->print();
		printf("\n");
	}

	void findstring(char* strscr) {
		root->findstring(strscr);
	}

	void findprfstring(char* prf) {
		root->findprfstring(prf);
	}
};