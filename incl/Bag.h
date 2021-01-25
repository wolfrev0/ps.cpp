#pragma once
#include "Core.h"
template<class T> struct Bag {
	struct N {
		T d = T();
		N* n = nullptr;
	};
	N *h = new N, *t = h;
	int cnt = 0;

	Bag() {}
	Bag(initializer_list<T> il) : cnt(sz(il)) {
		for(auto i : il) add(i);
	}

	void add(T x) {
		t = t->n = new N{x};
		cnt++;
	}
	void merge(Bag a) {
		t->n = a.h->n;
		t = a.t;
		a.h->n = nullptr;
		a.t = a.h;
		cnt += a.cnt;
		a.cnt = 0;
	}
	int size() const { return cnt; }
	void iter(Func<void(T&)> f) {
		N* c = h->n;
		while(c) f(c->d), c = c->n;
	}
	Arr<T> toArr() {
		Arr<T> ret;
		iter([&ret](T x) { ret.pushb(x); });
		return ret;
	}
	bool operator<(Bag a) const { return false; }  // for pair compare
};