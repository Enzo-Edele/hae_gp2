// ConsoleAppCour27-09.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

//<>fichier pris, ''fichier a nous
#include <iostream>
#include <string>
#include <unordered_map>


#include "IntArray.hpp"
#include "Vec.hpp"
#include "LinkedListExo.hpp"
#include "IntTree.hpp"
#include "FloatArray.hpp"
#include "Lib.hpp"
#include "StringTree.hpp"
#include "StringTreesDav.hpp"
#include "Recurrence.hpp"

using namespace std;

void TestVec4()
{
    Vec3 sapin;

    Vec3 vector1(1, 2, 3);
    Vec3 vector2(2, 4, 6);

    vector1.add(vector2);

    Vec4 v0(1, 2, 3, 4);
    Vec4 v1(2, 4, 6, 8);
    {
        Vec4 v2 = v0.add(v1);

        if (v2.x != 3) throw "Add";
        if (v2.y != 6) throw "Add";
        if (v2.z != 9) throw "Add";
        if (v2.w != 12) throw "Add";
        int here = 0;
    }
    {
        Vec4 v3 = v1.sub(v0);
        if (v3.x != 1) throw "Sub";
        if (v3.y != 2) throw "Sub";
        int here = 0;
    }
    {
        Vec4 v4 = v0.mul(v1);
        if (v4.x != 2) throw "Mul";
        if (v4.y != 8) throw "Mul";
        int here = 0;
    }
    {
        Vec4 v4 = v1.div(v1);
        if (v4.x != 1) throw "Div";
        if (v4.y != 1) throw "Div";
        int here = 0;
    }
    {
        Vec4* r0 = new Vec4();
        Vec4* r1 = new Vec4;
        Vec4* r2 = nullptr;

        Vec4* r3 = new Vec4[16];
        r3[4].incr(Vec4(666, 0, 0, 0));

        auto r34 = r3[4];
        auto r34bis = *(r3 + 4);

        int here = 0;
    }
}

static void assert(bool test) {
    if(!test) throw "assert";
};

void TestArray()
{
    {
        IntArray array(5);

        array.set(0, 1);
        array.set(1, 15);
        int test = array.get(1);
        test = array.get(0);
        int here = 0;
    }
    {
        IntArray a(8);
        assert(a.get(0) == 0);
        a.set(2, 666);
        a.set(a.getSize() - 1, 777);

        assert(a.get(2) == 666);
        assert(a.get(a.getSize() - 1) == 777);
        assert(a.get(5) == 0);

        int here = 0;
    }

    {
        IntArray a(5);
        for (int i = 0; i < a.getSize(); i++) {
            a.set(i, i * i);
            printf("% d", a.get(i));
        }
        printf("\n");
        printf("% d\n", a.SearchOrderInferior(-1));
        printf("% d\n", a.SearchOrderInferior(8));
        printf("% d\n", a.SearchOrderInferior(22));
        int verif = 0;
    }
    {
        IntArray a(5);
        for (int i = 0; i < a.getSize(); i++) {
            a.set(i, i * i);
            printf("% d", a.get(i));
            printf("\n");
        }
        a.insertOrderInferior(5);
        a.insertOrderInferior(54);
        a.insertOrderInferior(-5544);

        assert(a.IsSorted());
        int here = 0;
    }
    {
        IntArray b(5);
        b.set(0, 5);
        b.set(1, 3);
        b.set(2, 9);
        b.set(3, 8);
        b.set(4, 1);

        b.Sort();

        int test = b.getSize();

        int here = 0;
    }
}

int StrLen(const char* str) { //str est un tableau de longueur inconnu
    int idx = 0;
    while(str[idx] != 0){
        idx++;
    }
    return idx;
}
int StrLen2(const char* str) { //la même mais en servant de la diférence entre str et le start
    const char* start = str;
    while (*str != 0) {
        str++;
    }
    return str - start;
}
int StrLen3(const char* str) { //str est un tableau de longueur inconnu
    const char* start = str;
    while (*str) str++;
    return str - start;
}

int Countc(const char* str, char c) {
    int idx = 0;
    int Countc = 0;
    while (str[idx] != 0) {
        if (str[idx] == c)
            Countc++;
        idx++;
    }
    
    return Countc;
}

void StrCpy(char* nstr, const char* str) {
    int idx = 0;
    while (str[idx])
    {
        nstr[idx] = str[idx];
        idx++;
    }
}
void StrCpy2(char* nstr, const char* str) {
    while (*str)
    {
        //*nstr = str;


    }
}
void StrCpy3(char* nstr, const char* str) {
    int len = StrLen(str);
    for (int i = 0; i < len; i++)
        nstr[i] = str[i];
}

void StrCpy(char* nstr, const char* str, int nchars) {
    
}

void TestLinkedList() {
    LinkedListInt list;
    list.insert(2);
    list.insert(4);
    list.insert(1);
    list.insert(9);
    list.insert(7);
    list.insert(8);

    list.print();

    list.remove(4);
    list.remove(9);
    list.remove(8);
    list.remove(2);

    list.print();

    int here = 0;
}

static void TestTree() {
    IntTreeController r;

    /*r.insert(2);
    r.insert(1);
    r.insert(13);
    r.insert(-5);
    r.insert(666);
    r.insert(86);
    r.insert(-7);
    r.insert(42);
    r.insert(2077);
    r.insert(4);
    r.insert(-17);
    r.insert(-10);*/

    clock_t now = clock();

    srand (now);

    for (int i = 0; i < 10; i++) {
        r.insert(rand() % 20 - 10);
    }

    r.print();

    //for (auto v: r) {
    //    r.remove(v);
    //}

    r.print();

    r.remove(5);
    r.remove(3);

    printf("\n");
    r.print();

    int here = 0;
}

void testCour1(){
    //tableau 150 élem
    int tabStatic[150]; //static local sera détruit une fois hors fonction

    int* tabDynamique = nullptr; //dynamique gloabal sera pas détruit une fois hors fonction
    tabDynamique = new int[150];

    //tableau de carré 
    for (int i = 0; i < 150; i++)
    {
        tabStatic[i] = i * i;
    }

    //afficher à l'nvers
    for (int i = 149; i >= 0; i--) {
        printf("%d \n", tabStatic[i]);
    }

    FloatArray tabArray(5);

    tabArray.pushFirst(1);
    tabArray.pushFirst(2);
    //tabArray.set(3, 4);
    tabArray.pushFirst(3);

    tabArray.print();

    tabArray.pushLast(8);

    tabArray.print();

    tabArray.pushLast(9);
    tabArray.pushLast(10);

    tabArray.print();

    auto maFunction = [](int val) {
        //printf("%f ", val);
        cout << std::to_string(val) << " ";
    };

    tabArray.iter(maFunction);

    float totalSum = 0;
    auto sumFunction = [&totalSum](float val) {
         totalSum += val;
    };

    tabArray.iter(sumFunction);
    printf("\n %f", totalSum);
    float abc[3] = { 1, 3, 5 };
    FloatArray f = FloatArray::fromArray(abc, 3);
    f.print();
}

void TestLib() {
    char sapin[29] = "sapinchateignererableplatane";
    char buffer[512] = {};
    char lapin[6] = "lapin";

    int tab[15] = { 1,2,3,0,5,4,1,2,3,0,5,4 ,1,2,3 };
    int bufferTab[512] = {};

    Lib::MemCpyRec(buffer, sapin, 29);

    printf(buffer);
    printf("\n");

    char src ='r';
    char* srcStr = (char*)"igne";

    const char* test = Lib::StrChrRec(sapin, src);
    
    printf(test);
    printf("\n");

    char* magnet = Lib::StrStrRec(sapin, srcStr);
    printf(magnet);
    printf("\n");

    printf("%i \n", Lib::StrlenRec(sapin));
    printf("\n");

    assert(0 == Lib::StrCmp(lapin, "lapin"));
    assert(-1 == Lib::StrCmp(lapin, "lapinou"));
    assert(1 == Lib::StrCmp(lapin, "lapi"));
    assert(1 == Lib::StrCmp(lapin, "dauphin"));
    assert(-1 == Lib::StrCmp(lapin, "zébre"));
    printf("%i \n",Lib::StrCmp(lapin, "lapin"));
    printf("%i \n", Lib::StrCmp(lapin, "lapinou"));
    printf("%i \n", Lib::StrCmp(lapin, "lapi"));
    printf("%i \n", Lib::StrCmp(lapin, "dauphin"));
    printf("%i \n", Lib::StrCmp(lapin, "zébre"));

    int here = 0;
}

void TestStringTree() {
    StringTreeDavControler tree;

    tree.insert((char*)"meme");
    tree.insert((char*)"tutu");
    tree.insert((char*)"xoxo");
    tree.insert((char*)"tata");
    tree.insert((char*)"ababa");
    tree.insert((char*)"ete");
    tree.insert((char*)"papa");
    tree.insert((char*)"papaParis");

    tree.print();

    tree.remove((char*)"meme");
    tree.remove((char*)"xoxo");
    tree.remove((char*)"ababa");
    tree.remove((char*)"ete");
    tree.remove((char*)"papa");
    tree.remove((char*)"tata");
    tree.remove((char*)"tutu");
    tree.remove((char*)"papaParis");

    //tree.remove((char*)"plum");
    //tree.remove((char*)"miku");
    //tree.remove((char*)"lena");

    tree.print();

    tree.insert((char*)"steak");
    tree.insert((char*)"musique");
    tree.insert((char*)"fisc");
    tree.insert((char*)"StarWarsUnDeuxTrois");
    tree.insert((char*)"RAM");
    tree.insert((char*)"StarWarssepthuitneuf");
    tree.insert((char*)"sucre");
    tree.insert((char*)"ursaf");
    tree.insert((char*)"sfr");

    tree.print();

    tree.findprfstring((char*)"eak");
    tree.findprfstring((char*)"us");
    tree.findprfstring((char*)"is");

    tree.remove((char*)"ursaf");
    tree.remove((char*)"fisc");
    tree.remove((char*)"StarWarssepthuitneuf");
    tree.remove((char*)"sfr");

    tree.print();

    tree.findstring((char*)"musique");

    int here = 0;
};

void TestRecurrence() {
    int a = 5;
    int b = -3;
    int c = 0;
    c = Recurrence::Add(a, b);
    assert(c == 2);
    c = Recurrence::Add(a, -b);
    assert(c == 8);

    c = Recurrence::Sub(a, b);
    assert(c == 8);
    c = Recurrence::Sub(a, -b);
    assert(c == 2);

    c = Recurrence::Mul(a, -b);
    assert(c == 15);
    c = Recurrence::Mul(0, 1);
    assert(c == 0);
    c = Recurrence::Mul(1, 0);
    assert(c == 0);
    c = Recurrence::Mul(1, 2);
    assert(c == 2);
    c = Recurrence::Mul(2, 8);
    assert(c == 16);
    c = Recurrence::Mul(-2, 8);
    assert(c == -16);
    c = Recurrence::Mul(-2, -2);
    assert(c == 4);

    assert(0 == Recurrence::Div(0, 1));
    assert(0 == Recurrence::Div(1, 0));
    assert(3 == Recurrence::Div(6, 2));
    assert(2 == Recurrence::Div(4, 2));
}

int main()
{
    //TestVec4();
    //TestArray();
    //TestLinkedList();
    //TestTree();
    //testCour1();
    TestLib();
    //TestStringTree();
    //TestRecurrence();

    {
        char str1[] = { "abcaya" };
        char str2[] = { "creatototututata" };
        char str256[256] = {};

        assert(StrLen(str1) == 6);
        assert(Countc(str1, 'a') == 3);
        StrCpy(str256, str2);

        int here = 0;
    }
}