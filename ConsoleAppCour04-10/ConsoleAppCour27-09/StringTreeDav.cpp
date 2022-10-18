#include "StringTreesDav.hpp"

StringTreeDav* StringTreeDav::insert(std::string val)
{
	if (str < val) {
		if (left) {
			left = left->insert(val);
		}
		else {
			left = new StringTreeDav;
			left->str = val;
		}
	}
	else {
		if (right) {
			right = right->insert(val);
		}
		else {
			right = new StringTreeDav;
			right->str = val;
		}
	}
	return this;
}

StringTreeDav* StringTreeDav::remove(std::string val)
{
	auto templeft = left;
	auto tempright = right;
	if (str == val)
	{
		//printf("value find \n");
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
		if (str < val) {
			left = left->remove(val);
		}
	}

	if (right) {
		if (str > val) { 
			right = right->remove(val);
		}
	}

	return this;
}

void StringTreeDav::print()
{
	if (left)
		left->print();
	std::cout << str << ", ";
	//printf("%s, ", str);
	if (right)
		right->print();
}

StringTreeDav* StringTreeDavControler::findstring(std::string strscr) {
	if (root)
		return root->findstring(strscr);
	else
		return nullptr;
}

StringTreeDav* StringTreeDavControler::findprfstring(std::string strscr) {
	if (root)
		return root->findprfstring(strscr);
	else
		return nullptr;
}

StringTreeDav* StringTreeDav::findstring(std::string strscr)
{
	if (str == strscr)
	{
		std::cout << str << " find";
		return this;
	}
	if (left) {
		if (str < strscr) {
			return left->findstring(strscr);
		}
	}
	if (right) {
		if (str > strscr) { 
			return right->findstring(strscr);
		}
	}
	return nullptr;
}

StringTreeDav* StringTreeDav::findprfstring(std::string prf)
{
	if (strPaternCompare(str, prf))
	{
		std::cout << str << " prefixe \n";
		return this;
	}
	if (left) {
		if (str < prf) {
			return left->findprfstring(prf);
		}
	}
	if (right) {
		if (str > prf) {
			return right->findprfstring(prf);
		}
	}
	return nullptr;
}

bool StringTreeDav::strPrefixeCompare(std::string src, std::string prefix) {
	bool test = true;
	for (int i = 0; i < prefix.size(); i++)
	{
		if (test && src[i] != prefix[i]) {
			test = false;
		}
	}
	return test;
}

bool StringTreeDav::strPaternCompare(std::string src, std::string prefix) {
	bool test = true;
	for (int i = 0; i < src.size() - prefix.size(); i++) {
		test = true;
		for (int y = 0; y < prefix.size(); y++)
		{
			if (test && src[i + y] != prefix[y]) {
				test = false;
			}
		}
		if (test)
			return test;
	}
	return test;
}

static const char* Strchr(const char* src, const char* tok) {
	for (int i = 0; i < strlen(src) - strlen(tok); i++) {
		bool correspond = true;
		char* temptok = (char*)tok;
		char* tempsrc = (char*)src;
		for (int y = 0; y < strlen(tok); y++) {
			if (tempsrc != temptok) {
				correspond = false;
			}
			*temptok++;
			*tempsrc++;
		}
		if (correspond) {
			return src;
		}
		*src++;
	}
	return nullptr;
}