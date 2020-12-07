#pragma once
#include "Core.h"

template<class T, int bias=1>
struct XArr: public Arr<T>{
	XArr(int n=0, T init=T()):Arr<T>(n, init){}
	XArr(initializer_list<T> il):Arr<T>(il){}
	T& operator[](int i){return Arr<T>::operator[](i+bias);}
	const T& operator[](int i)const{return Arr<T>::operator[](i+bias);}
	T& at(int i){return *this[i];}
	const T& at(int i)const{return *this[i];}
};
