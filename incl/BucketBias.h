#pragma once
#include "Core.h"

//https://atcoder.jp/contests/arc119/tasks/arc119_c
struct BucketBias{
	void insert(int x){s++,++c[x+b];}
	void erase(int x){s--,--c[x+b];}
	void incall(int x){b-=x;}
	int operator[](int x){return c[x+b];}

	map<int,int> c;
	int b=0,s=0;
};