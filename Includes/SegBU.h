#pragma once
#include "Core.h"

template<typename T, typename F>
struct SegBU{
	SegBU(int n=0):n(n), tr(2*n, F::id()){}
	void upd(int p, T val){
		for (tr[p+=n]=val; p>1; p>>=1)
			tr[p>>1]=F::q(tr[p],tr[p^1]);
	}

	T q(int s, int e) {
		T res=F::id();
		for (s+=n,e+=n; s<e; s>>=1,e>>=1) {
			if (s&1)res=F::q(res,tr[s++]);
			if (e&1)res=F::q(res,tr[--e]);
		}
		return res;
	}
protected:
	int n;
	Arr<T> tr;
};