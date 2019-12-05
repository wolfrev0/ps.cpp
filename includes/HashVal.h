#pragma once
#include "Core.h"

struct HashVal{
	u64 h[2]{};
	
	void add_as_seq(HashVal x){
		rep(i,2)
			h[i]*=p[i], h[i]+=x.h[i];
	}
	
	void add_as_set(HashVal x){
		rep(i,2)
			h[i]+=fp(p[i], x.h[i]);
	}
	
	void rem_as_seq(HashVal x){
		rep(i,2)
			h[i]*=p[i], h[i]-=x.h[i];
	}
	
	void rem_as_set(HashVal x){
		rep(i,2)
			h[i]-=fp(p[i], x.h[i]);
	}
	
	HashVal operator+(const HashVal& r)const{return {h[0]+r.h[0],h[1]+r.h[1]};}
	HashVal operator-(const HashVal& r)const{return {h[0]-r.h[0],h[1]-r.h[1]};}
	HashVal operator+=(const HashVal& r){return *this=*this+r;}
	HashVal operator-=(const HashVal& r){return *this=*this-r;}
	HashVal operator-()const{return {-h[0], -h[1]};}
	bool operator==(const HashVal& r)const{return h[0]==r.h[0]&&h[1]==r.h[1];}
	bool operator<(const HashVal& r)const{return h[0]==r.h[0]?h[1]<r.h[1]:h[0]<r.h[0];}
	
private:
	static constexpr u64 p[2]={(u64)prime, (u64)mod};
	
	u64 fp(u64 x, int p){
		if(!p)
			return 1;
		u64 z=fp(x,p/2);
		return z*z*(p%2?x:1);
	}
};

ostream& operator<<(ostream& s, const HashVal& n) { return s<<'('<<(unsigned)n.h[0]<<','<<(unsigned)n.h[1]<<')'; }