#pragma once
#include "Core.h"

template<typename T>
struct XArr{
	XArr(int n=0, int offset=1, T init=T()):arr(n+offset, init), o(offset){}
	T& operator[](int i){return arr[i+o];}
	//const T& operator[](int i)const{return arr[i+o];}
	Arr<T> arr;
	int o;
};