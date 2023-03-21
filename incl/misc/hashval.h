#pragma once
#include "core/base.h"

template<int m1=u64(1e9+9),int m2=u64(1e9+7)>
struct HashVal{
	u64 h[2];
	HashVal():HashVal(0,0,0){}
	HashVal(u64 h1):HashVal(h1,h1,1){}
	HashVal(u64 h1,u64 h2,int cnt):cnt(cnt){h[0]=h1,h[1]=h2;}

	//Sequential Hash
	void push_back(HashVal x){
		for(int i=0;i<2;i++)
			h[i]=h[i]*fp(p[i],x.cnt)+x.h[i];
		cnt+=x.cnt;
	}
	void push_front(HashVal x){
		for(int i=0;i<2;i++)
			h[i]=x.h[i]*fp(p[i],cnt)+h[i];
		cnt+=x.cnt;
	}
	void pop_back(HashVal x){
		for(int i=0;i<2;i++)
			h[i]=(h[i]-x.h[i])*inv(fp(p[i],x.cnt));
		cnt-=x.cnt;
	}
	void pop_front(HashVal x){
		for(int i=0;i<2;i++)
			h[i]-=x.h[i]*fp(p[i],cnt);
		cnt-=x.cnt;
	}

	//Set Hash
	void insert(HashVal x){
		for(int i=0;i<2;i++)
			h[i]+=fp(p[i],x.h[i]);
		cnt++;}
	void erase(HashVal x){
		for(int i=0;i<2;i++)
			h[i]-=fp(p[i],x.h[i]);
		cnt--;}

	int size()const{return cnt;}
	HashVal operator+(const HashVal& r)const{
		auto ret=*this;
		ret.push_back(r);
		return ret;
	}
	HashVal operator-(const HashVal& r)const{
		auto ret=*this;
		ret.pop_back(r);
		return ret;
	}
	HashVal operator+=(const HashVal& r){return *this=*this+r;}
	HashVal operator-=(const HashVal& r){return *this=*this-r;}
	bool operator==(const HashVal& r)const{return h[0]==r.h[0] and h[1]==r.h[1];}
	bool operator<(const HashVal& r)const{return h[0]==r.h[0]?h[1]<r.h[1]:h[0]<r.h[0];}
private:
	int cnt;
	static constexpr u64 p[2]={m1,m2};

	//지금은 cnt 길이가 가변이라 constexpr효과를 못받지만,직접 짜거나 개선하면
	//cxp효과로 log제거 가능하다.
	constexpr u64 fp(u64 x,u64 p){
		if(!p) return 1;
		u64 z=fp(x,p/2);
		return z*z*(p%2?x:1);}
	// inverse of p in modulo 2^64 (see euler's theorem)
	constexpr u64 inv(u64 x){return fp(x,9223372036854775807);}
};

template<int m1,int m2>
ostream& operator<<(ostream& s,const HashVal<m1,m2>& n){
	return s<<'('<<(unsigned)n.h[0]<<','<<(unsigned)n.h[1]<<')';}
