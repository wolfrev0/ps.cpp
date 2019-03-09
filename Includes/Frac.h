#pragma once
#include "Core.h"

template<typename T>
struct Frac{
	T a,b;
	Frac(T a=0, T b=1):a(a),b(b){normalize();}
	bool operator<(const Frac& r)const{
    if(r.is_nan())
      return false;
    if(is_nan())
      return true;
    return a*r.b<r.a*b;
  }
	bool operator==(const Frac& r)const{return a==r.a && b==r.b;}
  Frac operator+(const Frac& r)const{return {a*r.b+r.a*b, b*r.b};}
	Frac operator*(const Frac& r)const{return {a*r.a, b*r.b};}
	Frac operator/(const Frac& r)const{return (*this)*Frac(r.b,r.a);}
	bool is_inf()const{return a&&!b;}
	bool is_nan()const{return !a&&!b;}
  bool is_int()const{return b&&!(a%b);}
  //a is sign <if normalized>
  int sign()const{return a>=0?1:-1;}
  T to_integer(){return a/b;}
	f64 to_f64(){return (f64)a/b;}
  T ceil()const{return a/b+(sign()>0)*!!(a%b);}
  T floor()const{return a/b-(sign()<0)*!!(a%b);}
	void normalize(){
		if(is_nan())
			return;
		if(is_inf()){
			a=1;
			return;
		}

    T g = gcd(a,b); 
    a/=g; b/=g;
    if(b<0)
      a*=-1, b*=-1;
	}

  static Frac<T> inf(){return {1,0};}
};

template<typename T>
ostream& operator<<(ostream& s, const Frac<T>& n){return s<<n.a<<'/'<<n.b;}