#pragma once

#include <string>

struct EntryInt {
public:
	int value;

	EntryInt* prev = nullptr;
	EntryInt* next = nullptr;

	~EntryInt(){
		printf("Delete entryint \n");
	};
};

class LinkedListInt{
public:
	EntryInt* root = nullptr;

	void insert(int val);
	void remove(int val);
	void print(); //prints the list with printf
};