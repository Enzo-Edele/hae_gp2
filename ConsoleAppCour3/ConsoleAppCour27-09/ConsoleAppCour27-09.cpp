// ConsoleAppCour27-09.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

//<>fichier pris, ''fichier a nous
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

struct Vec2{
    float x = 0;
    float y = 0;
    Vec2(){}
    Vec2(float _x, float _y) {
        x = _x;
        y = _y;
    }

    void add(Vec2 v) {
        x += v.x;
        y += v.y;
    }

    void addRef(Vec2& v) {
        x += v.x;
        y += v.y;
    }

    void addPtr(Vec2 * v) {
        x += v->x;
        y += v->y;
    }
};

struct Vec3 : public Vec2 {
    float z = 0;

    Vec3() {}

    Vec3(float _x, float _y, float _z) : Vec2(_x, _y) { //le constructeur de V2 va faire son propre truc
        z = _z;
    }
    
    void add(Vec3 v) {
        Vec2::add(v);
        z += v.z;
    }
    void addRef(Vec3& v) { //façon idiomatique est d'ajouté const  : addRef(const Vec3& v) { const
        Vec2::addRef(v);
        z += v.z;
    }
    void addPtr(Vec3 * v) {
        Vec2::addPtr(v);
        z += v->z;
    }
};

struct Vec4 {
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    float w = 0.0f;

    Vec4() {}

    Vec4(float _x, float _y, float _z, float _w){ 
        x = _x;
        y = _y;
        z = _z;
        w = _w;
    }

    Vec4 add(const Vec4& v) {
        return Vec4(x + v.x, y + v.y, z + v.z, w + v.w);
    }

    Vec4 sub(const Vec4& v) {
        return Vec4(x - v.x, y - v.y, z - v.z, w - v.w);
    }

    Vec4 mul(const Vec4& v) {
        return Vec4(x * v.x, y * v.y, z * v.z, w * v.w);
    }

    Vec4 div(const Vec4& v) {
        return Vec4(x / v.x, y / v.y, z / v.z, w / v.w);
    }

    void incr(const Vec4& v) {
        x += v.x;
        y += v.y;
        z += v.z;
        w += v.w;
    }
};

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
        delete[] newData;

    };

    void shiftRight(int targetIdx) {
        resize(size++);
        for (int i = size; i > targetIdx; i--)
            data[i] = data[i--];
    }

    void insertOrderInferior(int value)
    {
        int idx = 0;
        while (data[idx] < value) {
            idx++;
        }

        shiftRight(idx);

        set(idx, value);
    }

    ~IntArray() {
        delete[] data;
        size = 0;
    };

    int getSize() {
        return size;
    };

protected:
    int* data = nullptr;
    int size = 0;
};

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
        IntArray a(8);
        for (int i = 0; i < 8; i++)
            a.set(i, i * i);
        a.insertOrderInferior(5);
            //normalement on a une fonction predicate qui vérifie si l'invariant(tableau triée) est satisfait
        assert(a.get(0) == 0);
        assert(a.get(1) == 1);
        assert(a.get(2) == 4);
        assert(a.get(3) == 5);
        assert(a.get(4) == 9);

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

int main()
{
    TestVec4();
    TestArray();

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