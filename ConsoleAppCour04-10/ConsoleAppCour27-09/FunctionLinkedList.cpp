#include "LinkedListExo.hpp"

#include <string>

void LinkedListInt::insert(int val) {
	EntryInt* ptr = new EntryInt;
	ptr->value = val;
	if (!root) {
		root = ptr;
	}
	else {
		auto oldroot = root;
		root = ptr;
		oldroot->prev = root;
		root->next = oldroot;
	}
}

//fonction pour insérer à la fin

void LinkedListInt::remove(int val) {
	auto ptr = root;
	while (ptr)
	{
		auto prev = ptr->prev;
		auto next = ptr->next;
		if (ptr->value == val)
		{
			if (prev) prev->next = next;
			if (next) next->prev = prev;
			if (root == ptr)
				root = next;
			delete ptr;
			ptr = nullptr;
		}
		ptr = next;
	}
	delete ptr;
}

void LinkedListInt::print() {
	auto ptr = root;
	while (ptr != nullptr)
	{
		printf("%d, ", ptr->value);
		ptr = ptr->next;
	}
	printf("\n");
}