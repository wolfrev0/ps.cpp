#pragma once
#include "Core.h"

struct Frac
{
	ll a, b;
	Frac(ll a=0, ll b=1):a(a),b(b){normalize();}
	inline ull hash()const{return (ull)a*prime+(ull)b;}
	inline bool operator<(const Frac& r)const { return (b<0) ^ (r.b<0) ? a * r.b > r.a*b : a*r.b < r.a*b; }
	inline bool operator==(const Frac& r)const { return a * r.b == r.a*b; }
	inline Frac operator*(const Frac& r)const { return {a*r.a, b*r.b};}
	inline Frac operator/(const Frac& r)const { return *this * Frac(r.b, r.a);}
	inline bool is_inf()const{return a&&!b;}
	inline bool is_nan()const{return !a&&!b;}
	inline ld to_ld(){return (ld)a/b;}
	inline void normalize(){
		if(is_nan())
			return;
		if(is_inf()){
			a=1;
			return;
		}
		ll g = gcd(a,b); 
		a/=g; b/=g;
	  if(b<0)
		  a*=-1, b*=-1;
	}
};

ostream& operator<<(ostream& s, const Frac& n) { return s <<n.a<<'/'<<n.b; }