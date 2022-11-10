// ConsoleAppCour27-09.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

//<>fichier pris, ''fichier a nous
#include <iostream>
#include <string>
#include <unordered_map>

#include "Int64Array.hpp"
#include "Int64ArrayRedo.hpp"
#include "LinkedList.hpp"

#include "BinaryTree.hpp"

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
    Lib lib;
    Int64ArrayRedo array(16);

    array.PushBack(5);
    array.PushBack(10);
    array.PushBack(20);
    array.PushBack(22);
    array.PushBack(27);
    array.PushBack(33);
    array.PushBack(49);
    array.PushBack(52);

    auto sorted = Int64ArrayRedo::Sort(array);

    sorted->print();

    printf("%i \n", sorted->BinarySearchIt(10) + 1);
    printf("%i \n", sorted->BinarySearchIt(52) + 1);
    printf("%i \n", sorted->BinarySearchIt(33) + 1);
    //printf("%i \n", sorted->BinarySearchIt(500));

    int end = 0;
}

void TestChrono2() {  //a reprendre sur git
    Lib lib;

    int sz = 256;
    Int64ArrayRedo t1(sz);
    t1.FillWithRandom(sz);
    t1.QSort();
    auto st0 = lib.GetTimeStamp();
    t1.SequentialSearch(lib.random());
    auto st1 = lib.GetTimeStamp();
    cout << to_string(st1 - st0) << "s \n";

    
    Int64ArrayRedo t2(1);
    t2.FillWithRandom(sz);
    t2.QSort();
    auto st20 = lib.GetTimeStamp();
    t1.BinarySearch(lib.random());
    auto st2 = lib.GetTimeStamp();
    cout << to_string(st2 - st1) << "s \n";

    int end = 0;
}

void TestChrono() {
    Lib lib;
    auto st0 = lib.GetTimeStamp();

    int sz = 256;
    Int64ArrayRedo t1(1);
    t1.FillWithRandom(sz);
    t1.InsertSort(t1);
    auto st1 = lib.GetTimeStamp();
    cout << to_string(st1 - st0) << "s \n";

    auto st20 = lib.GetTimeStamp();
    Int64ArrayRedo t2(1);
    t2.FillWithRandom(sz);
    t2.InsertSort(t2);
    auto st2 = lib.GetTimeStamp();
    cout << to_string(st2 - st1) << "s \n";

    auto timing0 = (st1 - st0);
    auto timing1 = (st2 - st20);

    cout << "timing 1 compared to timing 0 = " << to_string(timing1 / timing0);

    int end = 0;
}

void TestBinary() {
    IntBinaryTree intTree;

    intTree.Insert(7);
    intTree.Insert(4);
    intTree.Insert(15);
    intTree.Insert(33);
    intTree.Insert(86);

    intTree.print();

    intTree.Remove(15);

    intTree.print();

    stringBinaryTree stringTree;

    stringTree.Insert("Micromania");
    stringTree.Insert("2k");
    stringTree.Insert("sega");
    stringTree.Insert("ea");
    stringTree.Insert("nintendo");

    stringTree.print();

    stringTree.Remove("ea");

    stringTree.print();

    floatBinaryTree floatTree;

    floatTree.Insert(1.2);
    floatTree.Insert(8.6);
    floatTree.Insert(4.2);
    floatTree.Insert(5.7);

    floatTree.print();

    floatTree.Remove(1.2);

    floatTree.print();

    IntBinaryTree remTree;

    for (int i = 0; i < 150; i++)
        remTree.Insert(i);

    cout << remTree.Size() << "\n";

    for (int i = 0; i < 150; i++)
        remTree.Remove(i);

    cout << remTree.Size() << "\n";
}

void TestLinkedList() {
    IntList listInt;
    FloatList listFloat;

    Node<int> toto(66);
    Node<float> tata(66.6);

    listInt.PushFront(5);
    listInt.PushFront(10);
    listInt.PushFront(3);
    listInt.PushFront(9);

    listInt.print();

    //listInt.RemoveOne(3);
    listInt.RemoveOne(5);
    listInt.RemoveOne(9);
    listInt.PushBack(15);
    listInt.PushBack(20);
    //listInt.RemoveOne(4);

    listInt.print();

    listFloat.PushFront(2.4);
    listFloat.PushFront(6.6);
    listFloat.PushFront(4.2);
    listFloat.PushFront(8.6);

    listFloat.print();

    listFloat.RemoveOne(2.4);
    //listFloat.RemoveOne(6.8);

    listFloat.print();
}

int main()
{
    clock_t init = clock();

    //TestInt64Array();
    //TestRedo64();
    //TestChrono2();
    //TestChrono();

    //TestLinkedList();

    TestBinary();
}