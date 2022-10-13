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

	int compareString(char* tested, char* src);

	int compareStringSame(char* tested, char* src);

	~StringTree() 
	{
		printf("Leaf Delete, \n");
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
		root = root->remove(str);
	}

	void print() {
		if (root)
			root->print();
		printf("\n");
	}
};