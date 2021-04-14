#pragma once
#include "Core.h"
#include "Monoid.h"

template<class T, class Q, class U> struct Seg {
	Seg(int n = 0) : n(n), tr(4 * n, Q::id()) {}
	T q(int s, int e) { s+=s<0?n:0, e+=e<0?n:0;
		if(s>e) return Q::f(q(s,n),q(0,e));
		assert(0<=s&&s<=e&&e<=n);
		return q(1, 0, n, s, e);
	}
	void upd(int idx, T val) { idx+=idx<0?n:0; upd(1,0,n,idx,val); }

private:
	T q(int c, int cs, int ce, int s, int e) {
		if(s >= ce || e <= cs) return Q::id();
		if(s <= cs && ce <= e) return tr[c];
		int cm = (cs + ce) / 2;
		return Q::f(q(c * 2, cs, cm, s, e), q(c * 2 + 1, cm, ce, s, e));
	}
	T upd(int c, int cs, int ce, int idx, T val) {
		if(idx >= ce || idx + 1 <= cs) return tr[c];
		if(idx <= cs && ce <= idx + 1) return tr[c] = U::f(tr[c], val);
		int cm = (cs + ce) / 2;
		return tr[c] = Q::f(upd(c * 2, cs, cm, idx, val),
		                    upd(c * 2 + 1, cm, ce, idx, val));
	}
	int n;
	Arr<T> tr;
};