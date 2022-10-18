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
		printf("value find \n");
		if (!left && !right) {
			delete this;
			return nullptr;
		}
		if (!left) {
			delete this;
			return tempright;
		}
		if (!right) {
			delete this;
			return templeft;
		}
		if (left && right) {
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
		//printf("left \n");
		if (compareString(left->str, val) == 1) { //les conditions sont pas bonnes
			left = left->remove(val);
		}
		left = left->remove(val);
	}

	if (right) {
		//printf("right \n");
		if (compareString(right->str, val) == -1) { //les conditions sont pas bonnes
			right = right->remove(val);
		}
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

void StringTree::findstring(char* strscr)
{
	if (compareStringSame(str, strscr) == 0)
	{
		printf("find : %s \n", str);
	}
	if (left) {
		if (compareString(left->str, strscr) == -1) { //les conditions sont pas bonnes
			left->findstring(strscr);
		}
		left->findstring(strscr);
	}

	if (right) {
		if (compareString(right->str, strscr) == 1) { //les conditions sont pas bonnes
			right->findstring(strscr);
		}
		right->findstring(strscr);
	}
}

void StringTree::findprfstring(char* prf)
{
	if (compareString(str, prf) == 0)
	{
		printf("find with prefixe : %s \n", str);
	}
	if (left) {
		//if (compareString(left->str, prf) == -1) { //les conditions sont pas bonnes
		//	left->findstring(prf);
		//}
		left->findprfstring(prf);
	}

	if (right) {
		//if (compareString(right->str, prf) == 1) { //les conditions sont pas bonnes
		//	right->findstring(prf);
		//}
		right->findprfstring(prf);
	}
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
	//printf("%s ", tested);
	//printf("compare to ");
	//printf("%s ", src);
	//printf("\n");
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
