#pragma once
#include "Core.h"

//https://atcoder.jp/contests/arc119/tasks/arc119_c
struct Counter{
	map<int,int> c;
	int b=0;
	int& operator[](int i){return c[i+b];}
	void incall(int x){b-=x;}
};