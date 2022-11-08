#include "Int64Array.hpp"

Int64Array::Int64Array(int size) {
	if (size <= 0)
		size = 16;
	data = (int64_t*)malloc(size * sizeof(int64_t));
	cursor = 0;
	allocSize = size;
	setZero(0, allocSize);
}
Int64Array::~Int64Array() {
	free(data);
	data = nullptr;
}

void Int64Array::ensure(int size) {
	if (size > allocSize) {
		int reaallocSize = allocSize + allocSize * 0.5f;
		data = (int64_t*)realloc(data, reaallocSize * sizeof(int64_t));
		allocSize = reaallocSize;
		setZero(cursor, allocSize);
	}
}
void Int64Array::pushBack(int64_t elem) {
	ensure(cursor + 1);
	data[cursor] = elem;
	cursor++;
}
void Int64Array::pushFront(int64_t elem) {
	ensure(cursor + 1);
	ShiftRightRec(0, cursor);
	data[0] = elem;
	cursor++;
}

void Int64Array::ShiftRight(int idx) {
	for (int i = cursor; i > idx; i--)
		data[i] = data[i - 1];
}
void Int64Array::ShiftRightRec(int stop, int idx) {
	if (idx == stop)
		return;
	if (!data[idx - 1])
		return;
	data[idx] = data[idx - 1];
	ShiftRightRec(stop, idx - 1);
}

void Int64Array::ShiftLeft(int idx) {
	if (idx < 0)
		return;
	if (!data[idx + 1]) {
		data[idx] = 0;
		return;
	}
	data[idx] = data[idx + 1];
	ShiftLeft(idx + 1);
}

void Int64Array::set_unsafe(int64_t elem, int idx) {
	data[idx] = elem;
}
void Int64Array::set(int64_t elem, int idx) {
	if (idx < 0 && idx >= cursor) throw "out of bounds";
	data[idx - 1] = elem;
}

void Int64Array::insert(int64_t elem, int idx) {
	ensure(cursor + 1);
	ShiftRightRec(idx - 1, cursor);
	data[idx - 1] = elem;
	cursor++;
}

void Int64Array::MemCpyRec(Int64Array dest, int size) {
	dest.ensure(size);
	if (size == 0)
		return;
	dest.pushFront(data[size]);
	MemCpyRec(dest, size - 1);
}

void Int64Array::print(int start) {
	if (!data[start]) {
		printf("\n");
		return;
	}
	printf("%i, ", (int)data[start]);
	start++;
	print(start);
}