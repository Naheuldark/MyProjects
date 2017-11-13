#ifndef VEC2_H
#define VEC2_H

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <cmath>

template<typename T>
class Vec2
{
public:
    T x, y;

    Vec2() : x(T(0)), y(T(0)) {}
    Vec2(T xx) : x(xx), y(xx) {}
    Vec2(T xx, T yy) : x(xx), y(yy) {}

    Vec2<T> operator * (const T &f) const { return Vec2<T>(x * f, y * f); }
    Vec2<T> operator * (const Vec2<T> &v) const { return Vec2<T>(x * v.x, y * v.y); }
    friend Vec2<T> operator * (const T &f, const Vec2 &v) { return Vec2<T>(v.x * f, v.y * f); }
    Vec2<T>& operator *= (const Vec2<T> &v) { x *= v.x, y *= v.y; return *this; }
    Vec2<T>& operator *= (const T &f) { x *= f, y *= f; return *this; }

    Vec2<T> operator - (const Vec2<T> &v) const { return Vec2<T>(x - v.x, y - v.y); }
    Vec2<T> operator - () const { return Vec2<T>(-x, -y); }

    Vec2<T> operator + (const Vec2<T> &v) const { return Vec2<T>(x + v.x, y + v.y); }
    Vec2<T>& operator += (const Vec2<T> &v) { x += v.x, y += v.y; return *this; }

    friend Vec2<T> operator / (const T &f, const Vec2 &v) { return Vec2<T>(f / v.x, f / v.y); }
    Vec2<T>& operator /= (const T &r) { x /= r, y /= r; return *this; }

    const T& operator [] (uint8_t i) const { return (&x)[i]; }
    T& operator [] (uint8_t i) { return (&x)[i]; }

    T norm() const { return x * x + y * y; }
    T length() const { return sqrt(norm()); }
    T dot(const Vec2<T> &v) const { return x * v.x + y * v.y; }
    Vec2& normalize()
    {
        T nor2 = norm();
        if (nor2 > 0) {
            T invNor = 1 / sqrt(nor2);
            x *= invNor, y *= invNor;
        }
        return *this;
    }
    T dist(const Vec2<T> &v) const { return sqrt(pow(v.x-x,2)+pow(v.y-y,2)); }


    friend std::ostream & operator << (std::ostream &os, const Vec2<T> &v)
    {
        os << "[" << v.x << " " << v.y << "]";
        return os;
    }
};

typedef Vec2<float> Vec2f;
typedef Vec2<int> Vec2i;

#endif // VEC3_H
