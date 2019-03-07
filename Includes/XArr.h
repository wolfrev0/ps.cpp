#pragma once
#include "Core.h"

template<typename T>
struct XArr{
  XArr(int n=0, int offset=1):offset(offset), arr(n+offset){}
  T& operator[](int idx){return arr[idx+offset];}
  auto begin(){return arr.begin();}
  auto end(){return arr.end();}
  int offset;
  vector<T> arr;
};