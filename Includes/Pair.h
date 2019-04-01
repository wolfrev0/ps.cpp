#pragma once 
#include "Core.h"

template<typename T, typename U>
struct Pair{
  T a; U b;
  Pair():Pair(T(), U()){}
  Pair(T a, T b):a(a), b(b){}
  Pair operator+(const Pair& r)const{return {a+r.a, b+r.b};}
  Pair operator+=(const Pair& r){return *this=*this+r;}
  bool operator==(const Pair& r)const{return a==r.a&&b==r.b;}
  bool operator!=(const Pair& r)const{return !(*this==r);}
  bool operator<(const Pair& r)const{return a==r.a?b<r.b:a<r.a;}
};