#pragma once
#include "Core.h"
#include "Monoid.h"

template<class T, class Q, class U> struct SegBU {
	SegBU(int n = 0) : n(n), tr(2 * n, Q::id()) {}
	void upd(int i, T val) {
		i += n, tr[i] = U::f(tr[i], val);
		while(i >>= 1) tr[i] = Q::f(tr[i * 2], tr[i * 2 + 1]);
	}
	T q(int s, int e) {
		T r = Q::id();
		for(s += n, e += n; s < e; s >>= 1, e >>= 1) {
			if(s & 1) r = Q::f(r, tr[s++]);
			if(e & 1) r = Q::f(r, tr[--e]);
		}
		return r;
	}

protected:
	int n;
	Arr<T> tr;
};
