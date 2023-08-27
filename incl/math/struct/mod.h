#pragma once
#include "core/base.h"

template<class T=i32, class U=i64, T m=998244353> struct Mod{
	static_assert(m < numeric_limits<T>::max()/2);
	// Mod(T n=0):n(n){assert(0<=n && n<m);}
	Mod(U n=0):n((n%m+m)%m){}
	explicit operator T()const{return n;}
	explicit operator bool()const{return !!n;}

	Mod operator-()const{return n?m-n:0;}
	Mod operator+(const Mod& b)const{return n+b.n >= m ? n+b.n-m : n+b.n;}
	Mod operator-(const Mod& b)const{return n-b.n < 0 ? n-b.n+m : n-b.n;}
	Mod operator*(const Mod& b)const{return U(n)*b.n%m;}
	Mod operator/(const Mod& b)const{return *this*b.inv();}
	Mod operator+=(const Mod& b){return *this=*this+b;}
	Mod operator-=(const Mod& b){return *this=*this-b;}
	Mod operator*=(const Mod& b){return *this=*this*b;}
	Mod operator/=(const Mod& b){return *this=*this/b;}
	Mod pow(T a)const{ if(!a)return 1;auto z=pow(a>>1);return z*z*(a&1?*this:1);}
	//Mod inv()const{return this->pow(m-2);}
	Mod inv()const{auto [g,x,y]=xgcd(n, m);assert(g==1);return (x%m+m)%m;}

	bool operator==(const Mod& r)const{return n==r.n;}
	bool operator!=(const Mod& r)const{return !(*this==r);}
	bool operator<(const Mod& r)const{return n<r.n;}

	T n;
	tint xgcd(T a, T b)const{
		if(!b)return{a,1,0};
		auto [g,x,y]=xgcd(b,a%b);
		return{g,y,x-(a/b)*y};
	}
};
template<class T, class U, T m> istream& operator>>(istream& s,Mod<T,U,m>& n){ n=input1(s); return s;}
template<class T, class U, T m> ostream& operator<<(ostream& s,const Mod<T,U,m>& n){return osprint(s,n.n);}

//TODO: dynamic modint (barrett, montgomery)
