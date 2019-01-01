#pragma once
#include "Core.h"

struct Vec3 {
	using T = ScalarType;
	T x, y, z;
	explicit Vec3() :Vec3(0, 0, 0) {}
	explicit Vec3(T x, T y, T z) :x(x), y(y), z(z) {}
	inline Vec3 operator+(const Vec3& r)const { return Vec3(x+r.x, y+r.y, z+r.z); }
	inline Vec3 operator-()const { return Vec3(-x, -y, -z); }
	inline Vec3 operator-(const Vec3& r)const { return *this + -r; }
	inline Vec3 operator*(T r)const { return Vec3(x*r, y*r, z*r); }
	inline Vec3 operator/(T r)const { return Vec3(x/r, y/r, z/r); }
	inline Vec3 operator+=(const Vec3& r) { return *this=*this+r; }
	inline Vec3 operator-=(const Vec3& r) { return *this=*this-r; }
	inline Vec3 operator*=(T r) { return *this=*this*r; }
	inline Vec3 operator/=(T r) { return *this=*this/r; }
	inline bool operator==(const Vec3& r)const { return x == r.x && y == r.y && z == r.z; }
	inline bool operator!=(const Vec3& r)const { return !(*this == r); }
	inline bool operator<(const Vec3& r)const { return x==r.x?(y==r.y?z<r.z:y<r.y)?:x<r.x; }
	inline bool operator<=(const Vec3& r)const { return *this==r || *this<r; }
	inline bool operator>(const Vec3& r)const { return x==r.x?(y==r.y?z>r.z:y>r.y):x>r.x; }
	inline bool operator>=(const Vec3& r)const { return *this==r || *this>r; }
	inline T size()const { return hypot(x, y, z); }
	inline T sizesq()const { return dot(*this); }
	inline Vec3 normalize()const { return *this/size(); }
	inline T dot(const Vec3& r) const { return x*r.x + y*r.y + z*r.z; }
	inline T dot(const Vec3& a, const Vec3& b) const { return (a - *this).dot(b - *this); }
	inline Vec3 cross(const Vec3& r)const { return Vec3(0, 0, x*r.y - y*r.x); }
	inline Vec3 cross(const Vec3& a, const Vec3& b) const { return (a - *this).cross(b - *this); }
	inline T angle()const { return 0; }
	inline Vec3 project(const Vec3& p)const { Vec3 base = normalize(); return base * base.dot(p); }
	inline Vec3 rot(double rad)const{ throw 0; }
} zero3, err3 = Vec3(inf<Vec3::T>(), inf<Vec3::T>()), epsv3 = Vec3(eps, eps);