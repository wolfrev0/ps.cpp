#pragma once
#include "Core.h"
#include "Monoid.h"

//NOTE: Requires Commutativity
template<class T, class F> struct SegBU {
	SegBU(int n = 0) : n(n), tr(2 * n, F::idT()){}
	void upd(int i, T val) { i+=i<0?n:0;
		i += n, tr[i] = F::upd(tr[i], val);
		while(i >>= 1) tr[i] = F::f(tr[i * 2], tr[i * 2 + 1]);
	}
	T q(int s, int e) { s+=s<0?n:0, e+=e<0?n:0;
		if(s>e) return F::f(q(s,n),q(0,e));
		assert(0<=s&&s<=e&&e<=n);
		T r = F::idT();
		for(s += n, e += n; s < e; s >>= 1, e >>= 1) {
			if(s & 1) r = F::f(r, tr[s++]);
			if(e & 1) r = F::f(r, tr[--e]);
		}
		return r;
	}

protected:
	int n;
	Arr<T> tr;
};
