using namespace std;

#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <cstdlib>

static int Comparator(const void* ptr1, const void* ptr2);

class IntArray {
public:

    IntArray(int maxSize);

    int get(int idx);

    void set(int idx, int value);

    void resize(int nuSize);
    //warning this function break the invariant by inserting a sentient
    void shiftRight(int targetIdx);
    //invariant mon tableaux est trié
    void insertOrderInferior(int value);

    int SearchOrderInferior(int value);

    ~IntArray();

    int getSize();

    bool IsSorted();

    void Sort();

    void Add(int val);

protected:
    int* data = nullptr;
    int size = 0;
};
