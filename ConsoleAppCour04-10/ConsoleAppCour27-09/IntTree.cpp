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

/*IntTree* IntTree::remove(int val, IntTree* root)
{
	//check si == val et ensuite parcourir enfant
	if (left) {
		if (val < left->value) {
			left = left->remove(val, root);
		}
		else if (left->value == val) {
			left->value = -4269;
			if (left->left)
				left = left->left;
			reinsert(root);
			return this;
		}
	}
	if(right){
		if (val > right->value) {
			right = right->remove(val, root);
		}
		else if (right->value == val) {
			right->value = -4269;
			if (right->right)
				right = right->right;
			reinsert(root);
			return this;
		}
	}

	return this;
}*/

IntTree* IntTree::remove(int val, IntTree* root) {
	auto tempLeft = left;
	auto tempRight = right;
	if (val == value) {
		if (!left && !right)
		{
			delete this;
			return nullptr;
		}
		if (!left) {
			delete this;
			return tempRight;
		}
		if (!right) {
			delete this;
			return tempLeft;
		}
		if (right && left) {
			while (left)
			{
				auto tempValue = left->value;
				right = right->insert(tempValue);
				left = left->remove(tempValue, root);
			}
			delete this;
			return tempRight;
		}
	}
	if (left) {
		if (val <= left->value) {
			left = left->remove(val, root);
		}
	}
	if (right) {
		if (val >= right->value) {
			right = right->remove(val, root);
		}
	}
	return this;
}

/*IntTree* IntTree::remove(int val, IntTree* root) {
	if (val == value) {
		auto oldRight = right;
		auto oldLeft = left;

		if (!oldRight && !oldLeft) {
			delete this;
			return nullptr;
		}
		else if (!oldRight) {
			delete this;
			return oldLeft;
		}
		else if (!oldLeft)
		{
			delete this;
			return oldRight;
		}
		//else if(oldLeft && oldRight){
		//	delete this;
		//oldLeft->insert(oldRight->value);
			//return oldLeft;
		//}
	}
	return this;
}*/

void IntTree::print()
{
	if (left)
		left->print();
	printf("%d ", value);
	if (right)
		right->print();
}

IntTree* IntTree::reinsert(IntTree* root){
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
	return this;
}

IntTree* IntTree::reinsert(IntArray* tab) {
	tab->Add(value);
	if (left)
		left->reinsert(tab);
	if (right)
		right->reinsert(tab);
	return this;
}
