#include "IntTree.hpp"
#include "IntArray.hpp"

#include <string>

IntTree* IntTree::insert(int val)
{
	if (val < value) {
		if (left) {
			left = left->insert(val);
		}
		else {
			left = new IntTree();
			left->value = val;
		}
	}
	else {
		if (right)
			right = right->insert(val);
		else {
			right = new IntTree();
			right->value = val;
		}
	}
	return this;
}

IntTree* IntTree::remove(int val, IntTree* root)
{
	//check si == val et ensuite parcourir enfant
	if (left) {
		if (val < left->value) {
			left = left->remove(val, root);
		}
		else if (left->value == val) {
			left->value = -4269;
			left = nullptr;
			reinsert(root);
		}
	}
	if(right){
		if (val > right->value) {
			right = right->remove(val, root);
		}
		else if (right->value == val) {
			right->value = -4269;
			right = nullptr;
			reinsert(root);
		}
	}

	return this;
}

void IntTree::print()
{
	if (left)
		left->print();
	printf("%d ", value);
	if (right)
		right->print();
}

void IntTree::reinsert(IntTree* root){
	IntArray tab(0);
	IntArray* ptr = (IntArray*)&tab;
	if (left)
		left->reinsert(ptr);
	if (right)
		right->reinsert(ptr);

	for (int i = 0; i < tab.getSize(); i++)
	{
		root->insert(tab.get(i));
	}
}

void IntTree::reinsert(IntArray* tab) {
	tab->Add(value);
	if (left)
		left->reinsert(tab);
	if (right)
		right->reinsert(tab);
}
