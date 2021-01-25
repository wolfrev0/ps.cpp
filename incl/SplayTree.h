#pragma once
#include "Core.h"

// interface: 0-based half
// implement: 1-based half
template<class T> struct SplayTree {
	SplayTree() : rt(new N()) {
		bin.s = 0;
		ins(1, 0);
	}
	~SplayTree() { delete rt; }
	void upd(int s, int e, T val) {
		auto x = interval(s + 1, e + 1);
		lz(x) += val;
		renew(x, true);
	}
	T q(int s, int e) { return a(interval(s + 1, e + 1)); }
	void ins(int i, T v) {
		splay(nth(rt, i));
		auto rsav = r(rt);
		setr(rt, new N(v));
		setr(r(rt), rsav);
		renew(r(rt), true);
	}
	void rm(int i) {
		auto x = interval(i + 1, i + 2);
		setl(p(x), nullptr);
		renew(p(x), true);
		delete x;
	}

private:
	struct N {
		T v = 0, a = 0, lz = 0;
		int s = 1;
		N *p = 0, *l = 0, *r = 0;
		N(T v = 0) : v(v) {}
		~N() {
			if(l) delete l;
			if(r) delete r;
		}
	};
	N *rt, bin;
	T &v(N *x) { return x ? x->v : bin.v; }
	T &a(N *x) { return x ? x->a : bin.a; }
	T &lz(N *x) { return x ? x->lz : bin.lz; }
	int &s(N *x) { return x ? x->s : bin.s; }
	N *&p(N *x) { return x ? x->p : bin.p; }
	N *&l(N *x) { return x ? x->l : bin.l; }
	N *&r(N *x) { return x ? x->r : bin.r; }
	void setl(N *x, N *y) {
		if(x) x->l = y;
		if(y) y->p = x;
	}
	void setr(N *x, N *y) {
		if(x) x->r = y;
		if(y) y->p = x;
	}

	N *nth(N *x, int n) {
		prop(x);
		if(s(l(x)) > n) return nth(l(x), n);
		if(s(l(x)) < n) return nth(r(x), n - s(l(x)) - 1);
		return x;
	}
	N *interval(int s, int e) {
		auto x = nth(rt, s - 1), y = nth(rt, e);
		splay(x);
		setr(x, p(r(x)) = nullptr);
		splay(y), rt = x;
		;
		setr(x, y);
		renew(y, true);
		return l(r(x));
	}
	void renew(N *x, bool anc = false) {
		prop(x), prop(l(x)), prop(r(x));
		s(x) = s(l(x)) + 1 + s(r(x));
		a(x) = a(l(x)) + v(x) + a(r(x));
		if(anc and p(x)) renew(p(x), anc);
	}
	void splay(N *x) {
		if(!p(x)) return;
		if(p(p(x))) rot((x == l(p(x))) == (p(x) == p(p(l(x)))) ? p(x) : x);
		rot(x);
		splay(x);
	}
	void rot(N *x) {
		if(!p(x)) return;
		prop(p(x)), prop(l(p(x))), prop(r(p(x)));
		auto psav = p(x);
		if(auto pp = p(p(x))) {
			if(l(pp) == p(x)) setl(pp, x);
			else
				setr(pp, x);
		} else
			p(x) = nullptr, rt = x;
		if(x == l(psav)) setl(psav, r(x)), setr(x, psav);
		else
			setr(psav, l(x)), setl(x, psav);
		renew(psav), renew(x);
	}
	void prop(N *x) {
		if(!lz(x)) return;
		v(x) += lz(x);
		a(x) += lz(x) * s(x);
		lz(l(x)) += lz(x);
		lz(r(x)) += lz(x);
		lz(x) = 0;
	}
};
