// ConsoleAppCour27-09.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

//<>fichier pris, ''fichier a nous
#include <iostream>
#include <string>
#include <unordered_map>

#include "Int64Array.hpp"
#include "Int64ArrayRedo.hpp"

using namespace std;

static void assert(bool test) {
    if (!test) throw "assert";
};

void TestInt64Array(){
    Int64Array array(16);
    /*
    array.pushBack(1);
    array.print();
    array.pushBack(2);
    array.print();
    array.pushBack(3);
    array.print();
    array.pushBack(4);
    array.print();
    array.pushFront(5);
    array.print();
    array.pushFront(6);
    array.print();
    array.pushFront(7);
    array.print();
    array.pushFront(8);
    array.print();

    array.insert(10, 5);

    array.print();

    array.set_unsafe(42, 13);
    array.set(20, 5);
    array.set(55, 35);

    array.print();

    array.set_unsafe(30, 5);

    array.print();

    Int64Array arrayCpy(2);

    //array.MemCpyRec(arrayCpy, array.cursor);
    */
    clock_t now = clock();
    srand(now);

    array.pushFront(2);
    array.pushFront(4);
    array.pushFront(3);
    array.pushFront(5);

    array.print();

    printf("%i \n", array.searchPositionDav(5, 0));

    array.print();

    array.InsertSort(array);

    array.print();

    //Int64Array* sortedArray = Int64Array::sort(array);

    //sortedArray->print();

    int here = 0;
}

void TestRedo64() {
    Int64ArrayRedo array(16);

    array.PushBack(5);
    array.PushBack(7);
    array.PushBack(86);
    array.PushBack(1);
    array.PushBack(3);
    array.PushBack(9);
    array.PushBack(22);
    array.PushBack(4);

    auto sorted = Int64ArrayRedo::Sort(array);

    array.print();

    printf("%i", array.BinarySearch(9));
    printf("%i", array.BinarySearch(4));
    printf("%i", array.BinarySearch(3));

    //assert(array.BinarySearch())
}

int main()
{
    //TestInt64Array();
    TestRedo64();
}