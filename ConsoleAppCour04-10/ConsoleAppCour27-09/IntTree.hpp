#pragma once

#include "IntArray.hpp"

class IntTree {
public:
	int value = 0;

	IntTree* left = nullptr;
	IntTree* right = nullptr;

	IntTree* insert(int val);
	IntTree* remove(int val, IntTree* root);
	void print();

	IntTree* reinsert(IntTree* root);
	IntTree* reinsert(IntArray* tab);

	~IntTree() {
		printf("Node Delete, \n");
	}
};

class IntTreeController {
public:
	IntTree* root = nullptr;
	void insert(int val) {
		if (!root) {
			root = new IntTree();
			root->value = val;
		}
		else
			root = root->insert(val);
	}
	void remove(int val) {
		root = root->remove(val, root);
	}
	void print() {
		if (root)
			root->print();
	}
};