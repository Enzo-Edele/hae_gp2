#include <iostream>

class StringTreeDav {
public:
	std::string str;

	StringTreeDav* left = nullptr;
	StringTreeDav* right = nullptr;

	StringTreeDav* insert(std::string val);
	StringTreeDav* remove(std::string val);
	void print();

	StringTreeDav* findstring(std::string strscr);
	StringTreeDav* findprfstring(std::string prf);

	static bool strPrefixeCompare(std::string src, std::string prefix);
	static bool strPaternCompare(std::string src, std::string prefix);

	~StringTreeDav()
	{
		//printf("Leaf Delete, \n");
	}
};

class StringTreeDavControler {
public:
	StringTreeDav* root = nullptr;

	void insert(std::string str) {
		if (!root) {
			root = new StringTreeDav();
			root->str = str;
		}
		else
			root->insert(str);
	}

	void remove(std::string str) {
		//printf("Start remove : \n");
		root = root->remove(str);
	}

	void print() {
		if (root)
			root->print();
		printf("\n");
	}

	StringTreeDav* findstring(std::string strscr);

	StringTreeDav* findprfstring(std::string prf);
};