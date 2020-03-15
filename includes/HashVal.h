#pragma once
#include "Core.h"

struct HashVal{
	u64 h[2];
	HashVal(u64 h1=0, u64 h2=0, int cnt=0):cnt(cnt){ h[0]=h1; h[1]=h2; }
	
	void push_back(HashVal x){ rep(i,2) h[i]*=p[i], h[i]+=x.h[i]; cnt++; }
	void push_front(HashVal x){ rep(i,2) h[i]+=x.h[i]*fp(p[i],cnt); cnt++; }
	void pop_back(HashVal x){ rep(i,2) h[i]-=x.h[i], h[i]*=inv(p[i]); cnt--; }
	void pop_front(HashVal x){ rep(i,2) h[i]-=x.h[i]*fp(p[i],cnt-1); cnt--; }
	
	void insert(HashVal x){ rep(i,2) h[i]+=fp(p[i], x.h[i]); cnt++; }
	void erase(HashVal x){ rep(i,2) h[i]-=fp(p[i], x.h[i]); cnt--; }
	
	HashVal operator+(const HashVal& r)const{return HashVal(h[0]+r.h[0], h[1]+r.h[1], cnt+r.cnt);}
	HashVal operator-(const HashVal& r)const{return HashVal(h[0]-r.h[0], h[1]-r.h[1], cnt+r.cnt);}
	HashVal operator+=(const HashVal& r){return *this=*this+r;}
	HashVal operator-=(const HashVal& r){return *this=*this-r;}
	HashVal operator-()const{return HashVal(-h[0], -h[1]);}
	bool operator==(const HashVal& r)const{return h[0]==r.h[0]&&h[1]==r.h[1];}
	bool operator<(const HashVal& r)const{return h[0]==r.h[0]?h[1]<r.h[1]:h[0]<r.h[0];}
	
private:
	int cnt;
	static cxp u64 p[2]={u64(1e9+9), u64(1e9+7)};
	
	//지금은 cnt 길이가 가변이라 cxp효과를 못받지만, 직접 짜거나 개선하면 cxp효과로 log제거 가능하다.
	cxp u64 fp(u64 x, u64 p){
		if(!p)
			return 1;
		u64 z=fp(x,p/2);
		return z*z*(p%2?x:1);
	}
	//inverse of p in modulo 2^64 (see euler's theorem)
	cxp u64 inv(u64 x){ return fp(x,9223372036854775807); }
};

ostream& operator<<(ostream& s, const HashVal& n) { return s<<'('<<(unsigned)n.h[0]<<','<<(unsigned)n.h[1]<<')'; }