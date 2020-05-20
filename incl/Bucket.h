#pragma once
#include "Core.h"

template<int n>
struct Bucket{
	int insert(int x){return sz+=!a[x]++;}
	int erase(int x){return sz-=!--a[x];}
	int size(){return sz;}
	int sz=0;
	int a[n]{};
};