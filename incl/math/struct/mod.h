#pragma once
#include "core/base.h"

//Mod객체로 DP할거면 반드시 optional 사용해야함. nan같은거 사용x
template<int m> struct Mod{
	Mod(i64 n=0):n((n%m+m)%m){}
	explicit operator int()const{return n;}
	explicit operator bool()const{return !!n;}

	Mod operator-()const{return -n;}
	Mod operator+(const Mod& b)const{return n+b.n;}
	Mod operator-(const Mod& b)const{return n-b.n+m;}
	Mod operator*(const Mod& b)const{return n*b.n;}
	Mod operator/(const Mod& b)const{return *this*b.inv();}
	Mod operator+=(const Mod& b){return *this=*this+b;}
	Mod operator-=(const Mod& b){return *this=*this-b;}
	Mod operator*=(const Mod& b){return *this=*this*b;}
	Mod operator/=(const Mod& b){return *this=*this/b;}
	Mod pow(int a)const{ if(!a)return 1;auto z=pow(a/2);return z*z*(a%2?*this:1);}
	//Mod inv()const{return this->pow(m-2);}
	Mod inv()const{auto [g,x,y]=xgcd(n, m);assert(g==1);while(x<0)x+=m;return x;}

	Mod& operator++(){*this+=1ll;return *this;}
	Mod& operator--(){*this-=1ll;return *this;}
	Mod operator++(signed){auto ret=*this;++*this;return ret;}
	Mod operator--(signed){auto ret=*this;--*this;return ret;}

	bool operator==(const Mod& r)const{return n==r.n;}
	bool operator!=(const Mod& r)const{return !(*this==r);}
	bool operator<(const Mod& r)const{return n<r.n;}

	i64 n;
	tint xgcd(i64 a, i64 b)const{
		if(!b)return{a,1,0};
		auto [g,x,y]=xgcd(b,a%b);
		return{g,y,x-(a/b)*y};
	}
};
template<int m> ostream& operator<<(ostream& s,const Mod<m>& n){return s<<n.n;}