#pragma once
#include "Core.h"

template<typename T>
struct Vec3 {
	T x, y, z;
	explicit Vec3() :Vec3(0, 0, 0) {}
	explicit Vec3(T x, T y, T z) :x(x), y(y), z(z) {}
	Vec3 operator+(const Vec3& r)const { return Vec3(x+r.x, y+r.y, z+r.z); }
	Vec3 operator-()const { return Vec3(-x, -y, -z); }
	Vec3 operator-(const Vec3& r)const { return *this + -r; }
	Vec3 operator*(T r)const { return Vec3(x*r, y*r, z*r); }
	Vec3 operator/(T r)const { return Vec3(x/r, y/r, z/r); }
	Vec3 operator+=(const Vec3& r) { return *this=*this+r; }
	Vec3 operator-=(const Vec3& r) { return *this=*this-r; }
	Vec3 operator*=(T r) { return *this=*this*r; }
	Vec3 operator/=(T r) { return *this=*this/r; }
	bool operator==(const Vec3& r)const { return x == r.x && y == r.y && z == r.z; }
	bool operator!=(const Vec3& r)const { return !(*this == r); }
	bool operator<(const Vec3& r)const { return x==r.x?(y==r.y?z<r.z:y<r.y):x<r.x; }
	bool operator<=(const Vec3& r)const { return *this==r || *this<r; }
	bool operator>(const Vec3& r)const { return x==r.x?(y==r.y?z>r.z:y>r.y):x>r.x; }
	bool operator>=(const Vec3& r)const { return *this==r || *this>r; }
	T size()const { return hypot(x, y, z); }
	T sizesq()const { return dot(*this); }
	Vec3 normalize()const { return *this/size(); }
	T dot(const Vec3& r) const { return x*r.x + y*r.y + z*r.z; }
	T dot(const Vec3& a, const Vec3& b) const { return (a - *this).dot(b - *this); }
	Vec3 cross(const Vec3& r)const { return Vec3(0, 0, x*r.y - y*r.x); }
	Vec3 cross(const Vec3& a, const Vec3& b) const { return (a - *this).cross(b - *this); }
	T angle()const { return 0; }
	Vec3 project(const Vec3& p)const { Vec3 base = normalize(); return base * base.dot(p); }
	Vec3 rot(double rad)const{ throw 0; }
	
	static Vec3 inf(){ return {T::inf(), T::inf(), T::inf()}; }
	static Vec3 zero(){return {};};
};