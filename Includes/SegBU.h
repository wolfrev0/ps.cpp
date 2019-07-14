#pragma once
#include "Core.h"

template<typename T, T id=T()>
struct SegBU{
	SegBU(int n=0):n(n), tr(2*n, id){}
	void upd(int p, T val){
		for (tr[p+=n]=val; p>1; p>>=1)
			tr[p>>1]=fq(tr[p],tr[p^1]);
	}

	T q(int s, int e) {
		T res=id;
		for (s+=n,e+=n; s<e; s>>=1,e>>=1) {
			if (s&1)res=fq(res,tr[s++]);
			if (e&1)res=fq(res,tr[--e]);
		}
		return res;
	}
protected:
	int n;
	vector<T> tr;
	
	virtual T fq(const T& a, const T& b)=0;
};

template<typename T> struct SegBUSum:public SegBU<T>{
	SegBUSum():SegBU<T>(){}
	T fq(const T& a, const T& b)override{return a+b;}
};
template<typename T> struct SegBUMax:public SegBU<T,-inf<T>()>{
	SegBUMax():SegBU<T>(){}
	T fq(const T& a, const T& b)override{return max(a,b);}
};
template<typename T> struct SegBUMin:public SegBU<T,inf<T>()>{
	SegBUMin():SegBU<T>(){}
	T fq(const T& a, const T& b)override{return min(a,b);}
};