#pragma once
#include "core/base.h"

template<class T, unsigned pn=2>
struct Hash{
	static_assert(pn<=4);
	static const T p[4];
	T h[pn];
	Hash():Hash(0){}
	Hash(T hv):Hash({hv,hv,hv,hv},1){} //4 because maximum 4 mods
	Hash(initializer_list<T> hil,int cnt):cnt(cnt){
		auto it=hil.begin();
		for(int i=0;i<pn;i++)
			h[i]=*it++;
	}

	//Sequential Hash
	void push_back(Hash x){
		for(int i=0;i<pn;i++)
			h[i]=h[i]*fp(p[i],x.cnt)+x.h[i];
		cnt+=x.cnt;
	}
	void push_front(Hash x){
		for(int i=0;i<pn;i++)
			h[i]=x.h[i]*fp(p[i],cnt)+h[i];
		cnt+=x.cnt;
	}
	void pop_back(Hash x){
		for(int i=0;i<pn;i++)
			h[i]=(h[i]-x.h[i])*inv(fp(p[i],x.cnt));
		cnt-=x.cnt;
	}
	void pop_front(Hash x){
		for(int i=0;i<pn;i++)
			h[i]-=x.h[i]*fp(p[i],cnt);
		cnt-=x.cnt;
	}

	//Set Hash
	void insert(Hash x){
		for(int i=0;i<pn;i++)
			h[i]+=fp(p[i],x.h[i]);
		cnt++;}
	void erase(Hash x){
		for(int i=0;i<pn;i++)
			h[i]-=fp(p[i],x.h[i]);
		cnt--;}

	int size()const{return cnt;}
	Hash operator+(const Hash& r)const{
		auto ret=*this;
		ret.push_back(r);
		return ret;
	}
	Hash operator-(const Hash& r)const{
		auto ret=*this;
		ret.pop_back(r);
		return ret;
	}
	Hash operator+=(const Hash& r){return *this=*this+r;}
	Hash operator-=(const Hash& r){return *this=*this-r;}
	bool operator==(const Hash& r)const{return h[0]==r.h[0] and h[1]==r.h[1];}
	bool operator<(const Hash& r)const{return h[0]==r.h[0]?h[1]<r.h[1]:h[0]<r.h[0];}
private:
	int cnt;
	T fp(T x, u64 p){return x.pow(p);}
	T inv(T x){return x.inv();}
};
//TODO: make it constexpr by Mod<> update
template<class T,unsigned pn>
const T Hash<T,pn>::p[4]={T((1ll<<61)-1),T(3),T((1ll<<31)-1),T(1e9+33)};

//NOTE: thuemorse sequence can break it
template <>
u64 Hash<u64,2>::fp(u64 x,u64 p){
	//NOTE: cnt를 고정하면 log 제거 가능함.
	if(!p) return 1;
	if(p==1) return x;
	u64 z=fp(x,p/2);
	return z*z*(p%2?x:1);
}
template <>
u64 Hash<u64,2>::inv(u64 x){
	return fp(x,u64(-2));
}

template<class T, unsigned pn>
ostream& operator<<(ostream& s,const Hash<T, pn>& n){
	s<<'(';
	for(int i=0;i<pn;i++)
		s<<(unsigned)n.h[i]<<',';
	return s<<')';
}
