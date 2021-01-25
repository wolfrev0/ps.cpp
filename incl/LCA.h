#pragma once
#include "RootedTree.h"

template<class T> struct LCA : public RootedTree<T> {
	using P = RootedTree<T>;
	using P::cost;
	using P::dpt;
	using P::n;
	using P::p;

	LCA(const Arr<pair<int, T>>& p) : P(p), pp(n, Arr<int>(lgc(n), -1)) {
		rep(i, n) pp[i][0] = p[i].fi;
	}

	//(2^k)th ancestor of v
	int panc(int v, int k) {
		int& ret = pp[v][k];
		return ret != -1 ? ret : ret = panc(panc(v, k - 1), k - 1);
	}

	// kth ancestor or v
	int anc(int v, int k) {
		for(; k; k -= k & -k) v = panc(v, k & -k);
		return v;
	}

	int lca(int a, int b) {
		if(dpt[a] > dpt[b]) swap(a, b);
		for(int i = lgc(n) - 1; i; i--)
			if(dpt[panc(b, i)] >= dpt[a]) b = panc(b, i);
		if(a == b) return a;
		for(int i = lgc(n) - 1; i; i--)
			if(panc(a, i) != panc(b, i)) a = panc(a, i), b = panc(b, i);
		return panc(a, 0);
	}

	Arr<Arr<int>> pp;
};
