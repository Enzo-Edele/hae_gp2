#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

struct Vec2 {
    float x = 0;
    float y = 0;
    Vec2() {}
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

    void addPtr(Vec2* v) {
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
    void addRef(Vec3& v) { //fa�on idiomatique est d'ajout� const  : addRef(const Vec3& v) { const
        Vec2::addRef(v);
        z += v.z;
    }
    void addPtr(Vec3* v) {
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

    Vec4(float _x, float _y, float _z, float _w) {
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