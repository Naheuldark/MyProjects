#ifndef VEC3_H
#define VEC3_H

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <cmath>

template<typename T>
class Vec3
{
public:
    T x, y, z;

    Vec3() : x(T(0)), y(T(0)), z(T(0)) {}
    Vec3(T xx) : x(xx), y(xx), z(xx) {}
    Vec3(T xx, T yy, T zz) : x(xx), y(yy), z(zz) {}

    Vec3<T> operator * (const T &f) const { return Vec3<T>(x * f, y * f, z * f); }
    Vec3<T> operator * (const Vec3<T> &v) const { return Vec3<T>(x * v.x, y * v.y, z * v.z); }
    friend Vec3<T> operator * (const T &f, const Vec3 &v) { return Vec3<T>(v.x * f, v.y * f, v.z * f); }
    Vec3<T>& operator *= (const Vec3<T> &v) { x *= v.x, y *= v.y, z *= v.z; return *this; }
    Vec3<T>& operator *= (const T &f) { x *= f, y *= f, z *= f; return *this; }

    Vec3<T> operator - (const Vec3<T> &v) const { return Vec3<T>(x - v.x, y - v.y, z - v.z); }
    Vec3<T> operator - () const { return Vec3<T>(-x, -y, -z); }

    Vec3<T> operator + (const Vec3<T> &v) const { return Vec3<T>(x + v.x, y + v.y, z + v.z); }
    Vec3<T>& operator += (const Vec3<T> &v) { x += v.x, y += v.y, z += v.z; return *this; }

    friend Vec3<T> operator / (const T &f, const Vec3 &v) { return Vec3<T>(f / v.x, f / v.y, f / v.z); }
    Vec3<T>& operator /= (const T &r) { x /= r, y /= r, z /= r; return *this; }

    const T& operator [] (uint8_t i) const { return (&x)[i]; }
    T& operator [] (uint8_t i) { return (&x)[i]; }

    T norm() const { return x * x + y * y + z * z; }
    T length() const { return sqrt(norm()); }
    T dot(const Vec3<T> &v) const { return x * v.x + y * v.y + z * v.z; }
    Vec3<T> cross(const Vec3<T> &v) const { return Vec3<T>(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x); }
    Vec3& normalize()
    {
        T nor2 = norm();
        if (nor2 > 0) {
            T invNor = 1 / sqrt(nor2);
            x *= invNor, y *= invNor, z *= invNor;
        }
        return *this;
    }
    T dist(const Vec3<T> &v) const { return sqrt(pow(v.x-x,2)+pow(v.y-y,2)+pow(v.z-z,2)); }


    friend std::ostream & operator << (std::ostream &os, const Vec3<T> &v)
    {
        os << "[" << v.x << " " << v.y << " " << v.z << "]";
        return os;
    }
};

typedef Vec3<float> Vec3f;
typedef Vec3<int> Vec3i;

#endif // VEC3_H
