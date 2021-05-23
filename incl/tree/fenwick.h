#pragma once
#include "core/base.h"

template<class T> struct Fenwick {
	Fenwick(int n = 0) : n(n), tr(n + 1) {}

	T q(int i) { return q(i, i + 1); }
	T q(int s, int e) {
		if(s >= e) return T();
		s++, e++;  // ft idx base = 1
		return sum(e - 1) - sum(s - 1);
	}

	// x: 1-based order
	int binlift(int x) {
		int s = 0, p = 0;
		int i = 1;
		while(1 << (i + 1) <= n) i++;
		for(; i >= 0; i--) {
			if(p + (1 << i) < n and s + tr[p + (1 << i)] < x) {
				s += tr[p + (1 << i)];
				p += 1 << i;
			}
		}
		return p;
	}

	void upd(int i, T delta) {
		i++;
		while(i <= n) {
			tr[i] += delta;
			i += (i & -i);
		}
	}

	void RUPQu(int s, int e, T d) {
		upd(s, d);
		upd(e, -d);
	}
	T RUPQq(int i) { return sum(i + 1); }

private:
	int n;
	Arr<T> tr;

	T sum(int i) {
		T ans = T();
		while(i > 0) {
			ans += tr[i];
			i -= (i & -i);
		}
		return ans;
	}
};