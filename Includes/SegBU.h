#pragma once
#include "Core.h"

template<typename T, int n>
struct SegBU{
	SegBU(const T& id=T()):id(id) {fill(tree, tree+2*n, id);}
	void upd(int p, T val){
		for (tree[p+=n]=val; p>1; p>>=1)
			tree[p>>1]=fq(tree[p],tree[p^1]);
	}

	T q(int s, int e) {
		T res=id;
		for (s+=n,e+=n; s<e; s>>=1,e>>=1) {
			if (s&1)res=fq(res,tree[s++]);
			if (e&1)res=fq(res,tree[--e]);
		}
		return res;
	}
protected:
	virtual T fq(const T& a, const T& b)=0;
	T tree[2*n], id;
};

template<typename T, int n> struct SegBUSum:public SegBU<T,n>{T fq(const T& a, const T& b)override{return a+b;}};
template<typename T, int n> struct SegBUMax:public SegBU<T,n>{SegBUMax():SegBU<T,n>(-inf<T>()){} T fq(const T& a, const T& b)override{return max(a,b);}};
template<typename T, int n> struct SegBUMin:public SegBU<T,n>{SegBUMin():SegBU<T,n>(inf<T>()){} T fq(const T& a, const T& b)override{return min(a,b);}};