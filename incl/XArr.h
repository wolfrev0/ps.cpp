#pragma once
#include "Core.h"

template<typename T>
struct XArr{
	XArr(int n=0, int offset=1, T init=T()):arr(n, init), o(offset){}
	auto& front()const{return arr.front();}
	auto& back()const{return arr.back();}
	auto begin()const{return arr.begin();}
	auto end()const{return arr.end();}
	T& operator[](int i){return arr[i+o];}
	//const T& operator[](int i)const{return arr[i+o];}
	void push_back(const T& x){arr.push_back(x);}
	void emplace_back(T&& x){arr.emplace_back(x);}
	auto erase(auto s, auto e){return arr.erase(s,e);}
	Arr<T> arr;
	int o;
};
