#pragma once
#include "tree/seg/seg.h"

//not tested
template<Monoid Q>
struct Seg2D{
	using T=decltype(Q::id());
	int n;
	Arr<Seg<Q>> tr;
	Seg2D(u32 n=0,u32 m=0):n(bit_ceil(n)),tr(this->n*2,Seg<Q>(m)){}
	void upd(int y, int x,T val){for(y+=n;y;y>>=1)tr[y].upd(x,val);}
	T q(int ys,int ye,int xs,int xe){
		T rs=Q::id(),re=Q::id();
		for(ys+=n,ye+=n;ys<ye;ys>>=1,ye>>=1){
			if(ys&1)rs=Q::f(rs,tr[ys++].q(xs,xe));
			if(ye&1)re=Q::f(tr[--ye].q(xs,xe),re);
		}
		return Q::f(rs,re);
	}
};

//not my code (출처불명)
struct seg2d {
	static const int N = 1 << 10;
	struct Seg {
		int tr[2 * N];
		void upd(int i, int v) {
			for(i += N; i; i /= 2) tr[i] += v;
		}
		int get(int s, int e) {
			int r = 0;
			for(s += N, e += N; s <= e; s /= 2, e /= 2) {
				if(s % 2) r += tr[s++];
				if(e % 2 == 0) r += tr[e--];
			}
			return r;
		}
	} tr[2 * N];

	void upd(int x, int y, int v) {
		for(x += N; x; x /= 2) tr[x].upd(y, v);
	}

	int get(int xs, int xe, int ys, int ye) {
		int r = 0;
		for(xs += N, xe += N; xs <= xe; xs /= 2, xe /= 2) {
			if(xs % 2) r += tr[xs++].get(ys, ye);
			if(xe % 2 == 0) r += tr[xe--].get(ys, ye);
		}
		return r;
	}
};
