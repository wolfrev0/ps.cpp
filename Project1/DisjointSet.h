#pragma once
#include "Core.h"

struct DisjointSet {
	vector<int> par;

	DisjointSet(int n) :par(n) {
		forh(i, 0, n)
			par[i] = i;
	}

	void uni(int a, int b) {
		a = find(a);
		b = find(b);
		//if (a == b)
		//return;
		//sometimes this if statement needed. (ex: BOJ-4195)
		par[a] = b;
	}

	int find(int a) {
		if (par[a] == a)
			return a;
		return par[a] = find(par[a]);
	}
};