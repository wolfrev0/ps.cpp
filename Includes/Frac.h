#pragma once
#include "Core.h"

template<typename T>
struct Frac
{
	T a, b;
	bool reduction;
	Frac(T a=0, T b=1, bool reduction=false):a(a),b(b),reduction(reduction){normalize();}
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
		if(reduction){
			T g = gcd(a,b); 
			a/=g; b/=g;
			if(b<0)
				a*=-1, b*=-1;
		}
	}
	
	static inline Frac zero(){ return 0; }
	static inline Frac one(){ return 1; }
	static inline Frac inf() { return {I64::inf(),0}; }
};

template<typename T>
ostream& operator<<(ostream& s, const Frac<T>& n) { return s <<n.a<<'/'<<n.b; }