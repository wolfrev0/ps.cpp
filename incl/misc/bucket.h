#pragma once
#include "core/base.h"

struct Bucket{
	Bucket(int n):a(n){}
	void add(int x){vc++,kc+=!a[x]++;}
	void del(int x){vc--,kc-=!--a[x];}
	int operator[](int x){return a[x];}
	int kc=0,vc=0;
	Arr<int> a;
};