#pragma once
#include <cstdint>
#include <cstdlib>
#include <string>

class Int64Array {
public:
	int64_t* data = nullptr;
	int allocSize = 0;
	int cursor = 0;  //marque fin de tableau

	Int64Array(int size);
	~Int64Array();

	void ensure(int size);

	void pushBack(int64_t elem);
	void pushFront(int64_t elem);

	void ShiftRight(int idx);
	void ShiftRightRec(int stop, int idx);
	void ShiftLeft(int idx);
	void ShiftLeftDav(int start, int stop) {
		if (start >= stop - 1)
			int here = 0;
	}

	void set_unsafe(int64_t elem, int idx);
	void set(int64_t elem, int idx);

	void insert(int64_t elem, int idx);

	void MemCpyRec(Int64Array dest, int idx = 0);

	void print(int start = 0);

	void fillWithRandom(int nbElem) {
		if (nbElem == 0)
			return;
		pushBack((int64_t)rand() % 10 + 1);
		fillWithRandom(nbElem - 1);
	}

	int searchPosition(int64_t elem, int size) { //pas ouf de partir par la fin pour la recherche
		if (size < 0 || !data[size])             // repasser dessus poue check
			return -1;

		if (data[size] == elem)
			return size;

		return searchPosition(elem, size - 1);
	}

	int searchPositionDav(int64_t elem, int start = 0) {
		return _searchPositionDav(elem);
	}

	void removeAt(int idx) {
		ShiftLeft(idx);
		cursor--;
	}

	bool removeOne(int64_t elem) {
		int pos = searchPositionDav(elem, cursor);
		if (pos != -1) {
			data[pos] = 0;
			ShiftLeft(pos);
			cursor--;
			return true;
		}
		return false;
	}

	void removeAll(int64_t elem) {
		bool one = removeOne(elem);
		if (!one)
			return;
		removeAll(elem);
	}

	int64_t get(int pos){
		return data[pos];
	}
	//insert content of ref but in a sorted fashion
	static Int64Array* sort(Int64Array ref) {
		//alloue un tableau
		if (ref.allocSize == 0)
			return new Int64Array(1);
		auto res = new Int64Array(ref.allocSize);
		
		ref.addElementInSortedArray(0, *res);
		
		return res;
	}

	int sortedIndex(int64_t elem, int idx = 0) {
		if (idx < 0)
			throw "inferior to 0";

		if (idx > cursor)
			return cursor;

		if (elem < data[idx])
			return idx;

		return sortedIndex(elem, idx + 1);
	}

	void addElementInSortedArray(int pos, Int64Array& in) {
		if (pos >= cursor)
			return;

		int64_t elem = get(pos);

		int insertPos = in.sortedIndex(elem);
		if (insertPos == -1) {
			return;
		}

		in.insert(elem, insertPos);
		addElementInSortedArray(pos + 1, in);
	}

	void goThroughRef(Int64Array& in, int idx = 1){
		if (idx > in.cursor)
			return;

		int64_t elem = data[idx];  //faire un get pos
		int pos = in.sortedIndex(elem);
		//verif pos est valide

		in.insert(elem, pos);

		goThroughRef(in, idx++);
		//printf("gone through \n");
	}

	// 4 6 2 8 0
	// 4 6 2 8 0
	// 4 6 
	//

	void swap(int idx0, int idx1) {
		int64_t tmp = data[idx0];
		data[idx0] = data[idx1];
		data[idx1] = tmp;
	}

	void InsertSort(Int64Array& t) {
		for (int i = 1; i < cursor; i++) {
			int j = i;
			while (j > 0 && t.data[j] < t.data[j - 1]) {
				t.swap(j, j - 1);
				j--;
			}
		};
	}

protected:

	int _searchPositionDav(int64_t elem, int start = 0) { // repasser dessus poue check
		if (start < 0 || start >= cursor)
			return -1;
		if (data[start] == elem)
			return start;
		_searchPositionDav(elem, start + 1);
	}

	void setZero(int start, int end) {
		if (start >= end) {
			return;
		}
		data[start] = (int64_t)0;
		setZero(start + 1, end);
	};
};