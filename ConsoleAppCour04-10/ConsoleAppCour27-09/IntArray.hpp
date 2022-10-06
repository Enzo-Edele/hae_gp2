using namespace std;

#include <iostream>
#include <string>
#include <unordered_map>

int Comparator(const void* ptr1, const void* ptr2) {
    int* first = (int*)ptr1;
    int* second = (int*)ptr2;

    int val1 = *first;
    int val2 = *second;
    return first - second;
}

class IntArray {
public:

    IntArray(int maxSize) {
        //alloue data
        data = new int[maxSize];
        for (int i = 0; i < maxSize; i++) {
            data[i] = 0;
        }
        size = maxSize;
        //change taille reelle
    };

    int get(int idx) {
        if (idx < 0) throw "out of bound exeption, bound cannot be inf to 0";
        if (idx >= size) throw "out of bound exeption, bound cannot be sup to size";
        return data[idx];
    };
    void set(int idx, int value) {
        if (idx < 0) throw "out of bound exeption, bound cannot be inf to 0";
        if (idx >= size) throw "out of bound exeption, bound cannot be sup to size";
        data[idx] = value;
    };
    void resize(int nuSize) {
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
    //warning this function break the invariant by inserting a sentient
    void shiftRight(int targetIdx) {
        if ((targetIdx < 0) || (targetIdx >= size))
            return;
        for (int i = size - 1; i > targetIdx; --i)
            data[i] = data[i - 1];
        data[targetIdx] = 0;
    }
    //invariant mon tableaux est trié
    void insertOrderInferior(int value)
    {
        int idx = SearchOrderInferior(value);

        resize(getSize() + 1);

        shiftRight(idx);

        set(idx, value);
    }

    int SearchOrderInferior(int value) {
        int idx = 0;
        while ((data[idx] < value) && (idx < size)) {
            idx++;
        }
        return idx;
    }

    ~IntArray() {
        delete[] data;
        size = 0;
    };

    int getSize() {
        return size;
    };

    bool IsSorted() {
        int idx = 1;
        while ((data[idx - 1] < data[idx]) && idx < size) {
            idx++;
        }
        if (idx == size)
            return true;
        else
            return false;
    }

    void Sort()
    {
        qsort(data, getSize(), sizeof(int), Comparator);
    }

protected:
    int* data = nullptr;
    int size = 0;
};
