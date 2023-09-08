#pragma once
#include "core/base.h"
#include "misc/i128.h"

template<class T=i64>
struct Frac {
	T a,b;
	Frac(i64 a=0,i64 b=1):a(a),b(b) {normalize();}
	auto operator<=>(const Frac& r)const{
		if(is_nan() and r.is_nan()) return strong_ordering::equal;
		if(is_nan())return strong_ordering::less;
		if(r.is_nan())return strong_ordering::greater;
		return i128(a)*r.b<=>i128(r.a)*b;
	}
	Frac inf()const{return {1,0};}
	
	Frac operator-()const{return {-a,b};}
	Frac operator+(const Frac& r)const{return {a*r.b+r.a*b,b*r.b};}
	Frac operator-(const Frac& r)const{return *this+-r;}
	Frac operator*(const Frac& r)const{return {a*r.a,b*r.b};}
	Frac operator/(const Frac& r)const{return (*this)*Frac(r.b,r.a);}
	Frac operator+=(const Frac& r){return *this=*this+r;}
	Frac operator-=(const Frac& r){return *this=*this-r;}
	Frac operator*=(const Frac& r){return *this=*this*r;}
	Frac operator/=(const Frac& r){return *this=*this/r;}
	explicit operator int()const{return a/b;}
	explicit operator fp()const{return fp(a)/b;}
	bool is_singular()const{return !b;}
	bool is_infpos()const{return a>0&&!b;}
	bool is_infneg()const{return a<0&&!b;}
	bool is_nan()const{return !a&&!b;}
	bool is_int()const{return b&&!(a%b);}
	i64 ceil()const{return a/b+(a*b>0)*!!(a%b);}
	i64 floor()const{return a/b-(a*b<0)*!!(a%b);}
	i64 smaller_int()const{return is_int()?int(*this)-1:floor();}
	i64 larger_int()const{return is_int()?int(*this)+1:ceil();}
	void normalize(){
		if(is_singular()){if(a)a/=abs(a);return;}
		i64 g=gcd(a,b); a/=g,b/=g;
		if(b<0) a*=-1,b*=-1;
	}
};
template<class T>
ostream& operator<<(ostream& s,const Frac<T>& n) {
	return (n.is_int()?osprint(s,int(n)):osprint(s,n.a,'/',n.b));
}
