#pragma once
#include "Core.h"

struct DisjointSet
{
	static const int N = 1000000;
	int par[N];

	DisjointSet()
	{
		forh(i, 0, N)
			par[i] = i;
	}

	void uni(int a, int b)
	{
		a = find(a);
		b = find(b);
		//if (a == b)
		//return;
		//sometimes this if statement needed. (ex: BOJ-4195)
		par[a] = b;
	}

	int find(int a)
	{
		if (par[a] == a)
			return a;
		return par[a] = find(par[a]);
	}
};