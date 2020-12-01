#pragma once
#include "Core.h"
#include "Mod.h"

template<class T>
struct CumulQ{
	T acc;
	CumulQ(T init=T()):acc(init){}
	int size(){return sz(q);}
	void push(const T& x){f(acc, x);q.push(x);}
	void pop(){finv(acc, q.front());q.pop();}
private:
	queue<T> q;
	virtual void f(T& acc, const T& x)=0;
	virtual void finv(T& acc, const T& x)=0;
};

template<class T>
struct SumQ:public CumulQ<T>{
private:
	void f(T& acc, const T& x)override{acc+=x;}
	void finv(T& acc, const T& x)override{acc-=x;}
};

//T=u64: anti-hash unsafe
//T=Mod<mod>: anti-hash safe but collision unsafe
//HashPairQ: anti-hash safe and collision safe but slow.
template<typename T>
struct HashQ:public CumulQ<T>{
	using P=CumulQ<T>;
private:
	Arr<T> dp{1};
	T ppow(int x){
		if(!x)
			return 1;
		while(sz(dp)<=x)
			dp.resize(sz(dp)*2);
		auto& ret=dp[x];
		if(ret)
			return ret;
		return ret=ppow(x/2)*ppow(x/2)*(x%2?prime:1);
	}

	void f(T& acc, const T& x)override{acc*=prime;acc+=x;}
	void finv(T& acc, const T& x)override{acc-=ppow(P::size()-1)*x;}
};

template<int m1=mod, int m2=1073741783>
struct HashPairQ{
	HashQ<Mod<m1>> q1;
	HashQ<Mod<m2>> q2;
	void push(int x){q1.push(x), q2.push(x);}
	void pop(){q1.pop(), q2.pop();}
	i64 get()const{ return (i64(q1.acc.val()<<32)) + q2.acc.val(); }
};