#include "StringTree.hpp"

#include <iostream>

using namespace std;

StringTree* StringTree::insert(char* val)
{
	if (compareString(str, val) == -1) {
		if (left) {
			left = left->insert(val);
		}
		else {
			left = new StringTree;
			left->str = val;
		}
	}
	else {
		if (right) {
			right = right->insert(val);
		}
		else {
			right = new StringTree;
			right->str = val;
		}
	}
	return this;
}

StringTree* StringTree::remove(char* val)
{
	auto templeft = left;
	auto tempright = right;
	if (compareStringSame(str, val) == 0)
	{
		printf("j'ai vétrou");
		if (!left && !right) {
			delete this;
			return nullptr;
		}
		else if (!right) {
			delete this;
			return templeft;
		}
		else if (!left) {
			delete this;
			return tempright;
		}
		else {
			while (left)
			{
				auto tempVal = left->str;
				right = right->insert(tempVal);
				left = left->remove(tempVal);
			}
			delete this;
			return tempright;
		}
	}
	
	if (left) {
		//printf("%s", compareString(left->str, val));
		if (compareString(left->str, val) == -1)
			left = left->remove(val);
	}

	if (right) {
		//printf("%s", compareString(right->str, val));
		if (compareString(right->str, val) == -1)
			right = right->remove(val);
	}

	return this;
}

void StringTree::print()
{
	if (left)
		left->print();
	//cout << str << ", ";
	printf("%s, ", str);
	if (right)
		right->print();
}

int StringTree::compareString(char* tested, char* src) {
	int test = 0;
	for (int i = 0; i < strlen(src); i++)
	{
		if (test == 0 && *tested > *src) {
			test = -1;
		}
		if (test == 0 && *tested < *src) {
			test = 1;
		}
		*tested++;
		*src++;
	}
	return test;
}

int StringTree::compareStringSame(char* tested, char* src)
{
	int test = 0;
	if (strlen(tested) != strlen(src))
	{
		return -1;
	}
	for (int i = 0; i < strlen(src); i++)
	{
		if (test == 0 && *tested > *src) {
			test = -1;
		}
		if (test == 0 && *tested < *src) {
			test = -1;
		}
		*tested++;
		*src++;
	}
	return test;
}
