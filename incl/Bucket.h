#pragma once
#include "Core.h"

template<int n> struct Bucket{
	void insert(int x){vc++,kc+=!a[x]++;}
	void erase(int x){vc--,kc-=!--a[x];}
	int operator[](int x){return a[x];}
	int kc=0,vc=0;
	Arr<int> a=Arr<int>(n);
};