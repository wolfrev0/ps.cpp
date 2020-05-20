#pragma once
#include "Core.h"

template<typename T>
struct XArr: public Arr<T>{
	XArr(int n=0, const T& init=T(), int offset=1):Arr<T>(n+offset, init), o(offset){}
	T& operator[](int i){return at(i);}
	T& at(int i){return Arr<T>::at(i+o);}
	const T& operator[](int i)const{return at(i);}
	const T& at(int i)const{return Arr<T>::at(i+o);}
	int o;
};