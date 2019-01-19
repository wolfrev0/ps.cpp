#pragma once
#include "Core.h"

struct Frac
{
	i64 a, b;
	Frac(i64 a=0, i64 b=1):a(a),b(b){normalize();}
	inline u64 hash()const{return (u64)a*prime+(u64)b;}
	inline bool operator<(const Frac& r)const { return (b<0) ^ (r.b<0) ? a * r.b > r.a*b : a*r.b < r.a*b; }
	inline bool operator==(const Frac& r)const { return a * r.b == r.a*b; }
	inline Frac operator*(const Frac& r)const { return {a*r.a, b*r.b};}
	inline Frac operator/(const Frac& r)const { return *this * Frac(r.b, r.a);}
	inline bool is_inf()const{return a&&!b;}
	inline bool is_nan()const{return !a&&!b;}
	inline f64 to_f64(){return (f64)a/b;}
	inline void normalize(){
		if(is_nan())
			return;
		if(is_inf()){
			a=1;
			return;
		}
		i64 g = gcd(a,b); 
		a/=g; b/=g;
	  if(b<0)
		  a*=-1, b*=-1;
	}
	
	static inline Frac zero(){ return 0; }
	static inline Frac one(){ return 1; }
	static inline Frac inf() { return {Regular<i64>::inf(),0}; }
};

ostream& operator<<(ostream& s, const Frac& n) { return s <<n.a<<'/'<<n.b; }