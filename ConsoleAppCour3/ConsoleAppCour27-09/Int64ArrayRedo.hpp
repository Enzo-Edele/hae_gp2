#pragma once

#include <cstdlib>
#include <cstdint>
#include <string>
#include "Lib.hpp"

static int Comparator(const void* ptr1, const void* ptr2) {
	int64_t* first = (int64_t*)ptr1;
	int64_t* second = (int64_t*)ptr2;

	int64_t val1 = *first;
	int64_t val2 = *second;

	return (int)(val1 - val2);
}

class Int64ArrayRedo {
public:
	int allocSize = 0;
	int cursor = 0;
	int64_t* data = nullptr;

	Int64ArrayRedo(int alloc_size) {
		if (alloc_size <= 0)
			alloc_size = 16;
		data = (int64_t*)malloc(alloc_size * sizeof(int64_t));
		SetZero(0, alloc_size);
		cursor = 0;
		allocSize = alloc_size;
	}
	~Int64ArrayRedo() {
		free(data);
		data = nullptr;
	}

	int Size() {
		return cursor;
	}

	void Ensure(int size) {
		if (allocSize < size) {
			int reallocSize = std::max<int>(allocSize * 1.5, size);
			data = (int64_t*)realloc(data, reallocSize * sizeof(int64_t));
			SetZero(allocSize, reallocSize);
			allocSize = reallocSize;
		}
	}

	void SetUnsafe(int pos, int64_t elem) {
		data[pos] = elem;
	}
	int64_t GetUnsafe(int pos) {
		return data[pos];
	}

	void Set(int pos, int64_t elem) {
		if (pos < 0 || pos > cursor) throw "out of bounds exeption";
		SetUnsafe(pos, elem);
	}
	int64_t Get(int pos) {
		if (pos < 0 || pos > cursor) throw "out of bounds exeption";
		return GetUnsafe(pos);
	}

	void ShiftRight(int stop, int pos) {
		if (pos <= stop)
			return;
		data[pos] = data[pos - 1];
		ShiftRight(stop, pos - 1);
	}
	void ShiftLeft(int start, int stop) {
		if (start >= stop - 1)
			return;
		int64_t p0 = data[start];
		int64_t p1 = data[start + 1];
		ShiftLeft(start + 1, stop);
		data[start] = p1;
	}

	void PushFront(int64_t elem) {
		Ensure(cursor + 1);
		ShiftRight(0, cursor);
		data[0] = elem;
		cursor++;
	}
	void PushBack(int64_t elem) {
		Ensure(cursor + 1);
		data[cursor] = elem;
		cursor++;
	}

	void Insert(int pos, int64_t elem) {
		Ensure(cursor + 1);
		ShiftRight(pos, cursor);
		data[pos] = elem; //utiliser set
		cursor++;
	}

	void FillWithRandom(int nbElem) {
		if (nbElem <= 0)
			return;
		PushFront(rand());
		FillWithRandom(nbElem - 1);
	}
protected:
	int searchPosition(int64_t elem, int start = 0) {
		if (start < 0 || start >= cursor)
			return -1;
		//trouvé
		if (data[start] == elem)
			return start;
		//call back
		return searchPosition(elem, start + 1);
	}
public:
	int SearchPosition(int64_t elem) {
		return searchPosition(elem);
	}

	void RemoveAt(int pos) {
		ShiftLeft(pos, cursor);
		cursor--;
	}
	bool RemoveOne(int64_t elem){
		int pos = SearchPosition(elem);

		if (pos < 0)
			return false;

		ShiftLeft(pos, cursor);
		cursor--;
		return true;
	}
	void RemoveAll(int64_t elem) {
		bool one = RemoveOne(elem);

		//check if nothing remove
		if (!one)
			return;

		//call back
		RemoveAll(elem);
	}
protected:
	int searchOrderedIndex(int64_t elem, int start = 0) {
		//cas d'arret 0
		if (start < 0)
			return -1;
		//cas d'arret cursor
		if (start >= cursor)
			return cursor;
		//cas trouvé
		if (data[start] <= elem)
			return start;
			//call back
		return searchOrderedIndex(elem, start + 1);
	}
public:
	int SearchOrderedIndex(int64_t elem) {
		return searchOrderedIndex(elem);
	}

	void AddElementInSortedArray(int start, Int64ArrayRedo& in) {
		//cas d'arret size
		if (start >= Size())
			return;
		//get first elem
		int64_t elem = Get(start);

		//trouvé ou l'insérer dans tab triéé
			//si mauvais on return
		int pos = in.SearchOrderedIndex(elem);
		if (pos == -1)
			return;
		//insérer
		in.Insert(pos, elem);
		//in.print(0);
		AddElementInSortedArray(start + 1, in);
	}

	static Int64ArrayRedo* Sort(Int64ArrayRedo& ref) {
		//allouer un tableau
		if (ref.Size() == 0)
			return new Int64ArrayRedo(1);
		auto res = new Int64ArrayRedo(ref.Size());
		//insérer le content de ref dans un tableau trier
		ref.AddElementInSortedArray(0, *res);

		//return res le tableau alloer
		return res;
	}

	void print(int start = 0) {
		if (start == 0 && cursor == 0) {
			printf("[]\n");
			return;
		}
		if (start < 0 || start >= cursor) {
			printf("\n");
			return;
		}
		printf("%lld ,", data[start]);
		print(start + 1);
	}

	void swap(int idx0, int idx1) {
		int64_t tmp = data[idx0];
		data[idx0] = data[idx1];
		data[idx1] = tmp;
	}

	void InsertSort(Int64ArrayRedo& t) {
		for (int i = 1; i < cursor; i++) {
			int j = i;
			while (j > 0 && t.data[j] < t.data[j - 1]) {
				t.swap(j, j - 1);
				j--;
			}
		};
	}

	int SequentialSearch(int64_t elem)
	{
		for (int i = 0; i < Size(); i++)
		{
			if (data[i] == elem) {
				return i;
			}
		}
		return -1;
	}

	void QSort() {
		qsort(data, Size(), sizeof(int64_t), Comparator);
	}

	int BinarySearch(int64_t elem) {
		return binarySearch(elem, Size(), 0);
	}

	int BinarySearchIt(int64_t elem) {
		int min = 0;
		int max = Size();
		int pos = 0;
		while (min < max && data[pos] != elem)
		{
			pos = (min + max) / 2;
			if (data[pos] < elem)
				max = pos - 1;
			if (data[pos] > elem)
				min = pos + 1;
		}
		if (data[pos] = elem)
			return pos;
		else
			return -1;
	}

protected:
	int binarySearch(int64_t elem, int max, int min = 0) { //inverser min et max et un nid a bug future
		//cas pas find
		if (min > max)
			return -1;

		int pos = (min + max) / 2;

		//cas find
		if (data[min] == elem)
			return min;
		if (data[pos] == elem)
			return pos;
		if (data[max] == elem)
			return max;
		//cas inf
		if (data[pos] < elem)
			return binarySearch(elem, pos - 1, min + 1);
		//cas sup
		if (data[pos] > elem)
			return binarySearch(elem, max - 1, pos + 1);
	}

	void SetZero(int start, int end) {
		if (end <= start)
			return;
		data[start] = 0;
		SetZero(start + 1, end);
	}
};