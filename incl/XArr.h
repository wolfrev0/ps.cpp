#pragma once
#include "Core.h"

template<class T>
struct XArr: public Arr<T>{
	XArr(int n=0, T init=T(), int offset=1):Arr<T>(n, init), o(offset){}
	constexpr T& operator[](int i){return Arr<T>::operator[](i+o);}
	constexpr const T& operator[](int i)const{return Arr<T>::operator[](i+o);}
	constexpr T& at(int i){return *this[i];}
	constexpr const T& at(int i)const{return *this[i];}
	int o;
};
