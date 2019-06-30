#pragma once
#include "Core.h"

template<int n, typename T>
struct SegBU{
	//생성자 대신 선언에{}붙여도 되는데, gcc버그로 컴파일하다 죽는다.
	SegBU():tree(){}
	void upd(int p, T val){
		for (tree[p+=n]=val; p>1; p>>=1)
			tree[p>>1]=qf(tree[p],tree[p^1]);
	}

	T q(int s, int e) {
		T res=T();
		for (s+=n,e+=n; s<e; s>>=1,e>>=1) {
			if (s&1)res=qf(res,tree[s++]);
			if (e&1)res=qf(res,tree[--e]);
		}
		return res;
	}
protected:
	virtual T qf(const T& a, const T& b)=0;
	T tree[2*n];
};

template<int n, typename T> struct SegBUAdd:public SegBU<n,T>{T qf(const T& a, const T& b)override{return a+b;}};
template<int n, typename T> struct SegBUMax:public SegBU<n,T>{T qf(const T& a, const T& b)override{return max(a,b);}};
template<int n, typename T> struct SegBUMin:public SegBU<n,T>{T qf(const T& a, const T& b)override{return min(a,b);}};