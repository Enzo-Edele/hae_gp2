#include "IntArray.hpp"

int Comparator(const void* ptr1, const void* ptr2) {
    int* first = (int*)ptr1;
    int* second = (int*)ptr2;

    int val1 = *first;
    int val2 = *second;
    return val1 - val2;
};

IntArray::IntArray(int maxSize) {
    //alloue data
    data = new int[maxSize];
    for (int i = 0; i < maxSize; i++) {
        data[i] = 0;
    }
    size = maxSize;
    //change taille reelle
};
int IntArray:: get(int idx) {
    if (idx < 0) throw "out of bound exeption, bound cannot be inf to 0";
    if (idx >= size) throw "out of bound exeption, bound cannot be sup to size";
    return data[idx];
};

void IntArray::set(int idx, int value) {
    if (idx < 0) throw "out of bound exeption, bound cannot be inf to 0";
    if (idx >= size) throw "out of bound exeption, bound cannot be sup to size";
    data[idx] = value;
};

void IntArray::resize(int nuSize) {
    if (nuSize == size)
        return;

    bool grow = nuSize > size;

    auto newData = new int[nuSize];
    for (int i = 0; i < nuSize; i++)
        newData[i] = 0;

    int targetSize = (grow) ? size : nuSize;
    for (int i = 0; i < targetSize; i++)
        newData[i] = data[i];

    int* odata = data;
    data = newData;
    size = nuSize;
    delete[]odata;
};
void IntArray::shiftRight(int targetIdx) {
    if ((targetIdx < 0) || (targetIdx >= size))
        return;
    for (int i = size - 1; i > targetIdx; --i)
        data[i] = data[i - 1];
    data[targetIdx] = 0;
}

void IntArray::insertOrderInferior(int value)
{
    int idx = SearchOrderInferior(value);

    resize(getSize() + 1);

    shiftRight(idx);

    set(idx, value);
}

int IntArray::SearchOrderInferior(int value) {
    int idx = 0;
    while ((data[idx] < value) && (idx < size)) {
        idx++;
    }
    return idx;
}

IntArray::~IntArray() {
    delete[] data;
    size = 0;
};

int IntArray::getSize() {
    return size;
};

bool IntArray::IsSorted() {
    int idx = 1;
    while ((data[idx - 1] < data[idx]) && idx < size) {
        idx++;
    }
    if (idx == size)
        return true;
    else
        return false;
}

void IntArray::Sort()
{
    qsort(data, getSize(), sizeof(int), Comparator);
}