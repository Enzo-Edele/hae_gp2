// ConsoleAppCour27-09.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

//<>fichier pris, ''fichier a nous
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

struct Toto
{
    float x = 0.555f;
};

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

int main()
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
    }
    {
        Vec4 v3 = v1.sub(v0);
        if (v3.x != 1) throw "Sub";
    }
    {
        Vec4 v4 = v1.div(v1);
        if (v4.x != 1) throw "Div";
    }
    int here = 0;
}
