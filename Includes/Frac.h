#pragma once
#include "Core.h"

struct Frac
{
	ll a, b;
	Frac(ll a, ll b=1):a(b?a:1),b(b){}
	bool operator<(const Frac& r)const { return b<0 ^ r.b<0 ? a * r.b > r.a*b : a*r.b < r.a*b; }
	bool operator==(const Frac& r)const { return a * r.b == r.a*b; }
	Frac operator*(const Frac& r)const { return {a*r.a, b*r.b}; }
	Frac inv()const{return {b,a};}
	bool is_inf()const{return a&&!b;}
	bool is_nan()const{return !a&&!b;}
	ld to_ld(){return (ld)a/b;}
};