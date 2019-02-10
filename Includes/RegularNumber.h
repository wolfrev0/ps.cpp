#pragma once
#include "Core.h"

template<typename T>
struct Regular{
		T n;
		Regular(T n=0):n(n){}
		operator T()const{return n;}
		static Regular<T> zero(){return 0;}
		static Regular<T> one(){return 1;}
		//for bool inf (=1)
		static Regular<T> inf(){auto ret=numeric_limits<T>::max()/2; return ret?ret:1; }
};
template<typename T>
ostream& operator<<(ostream &os, Regular<T> n){return os<<n.n;}
template<typename T>
istream& operator>>(istream &is, Regular<T> &n){return is>>n.n;}
using Bool=Regular<bool>;
using I8=Regular<i8>;using I16=Regular<i16>;using I32=Regular<i32>;using I64=Regular<i64>;
using U8=Regular<u8>;using U16=Regular<u16>;using U32=Regular<u32>;using U64=Regular<u64>;
using F64=Regular<f64>;

#if __x86_64__ || __ppc64__
using i128 = __int128_t;
using u128 = __uint128_t;
using f128 = __float128;
template<>
struct Regular<i128>{
		i128 n;
		Regular(i128 n=0):n(n){}
		operator i128()const{return n;}
		static Regular<i128> zero(){return 0;}
		static Regular<i128> one(){return 1;}
		static Regular<i128> inf(){return ((u128(1)<<127)-1)/2;}
};
template<>
struct Regular<u128>{
		u128 n;
		Regular(u128 n=0):n(n){}
		operator u128()const{return n;}
		static Regular<u128> zero(){return 0;}
		static Regular<u128> one(){return 1;}
		static Regular<u128> inf(){return u128(-1)/2;}
};
template<>
struct Regular<f128>{
		f128 n;
		Regular(f128 n=0):n(n){}
		operator f128()const{return n;}
		static Regular<f128> zero(){return 0;}
		static Regular<f128> one(){return 1;}
		static Regular<f128> inf(){ return numeric_limits<f64>::max()/2; }
};
using I128=Regular<i128>; using U128=Regular<u128>; using F128=Regular<f128>;
ostream& operator<<(ostream &os, u128 n){
	string s;while(n){ s.push_back(n%10+'0');n/=10; }
	reverse(s.begin(), s.end());
  if(s.empty())
    s.push_back('0');
	return os<<s;
}
ostream& operator<<(ostream &os, i128 n){
  if(n<0){ os<<'-';n*=-1; }
	return os<<(u128)n;
}
ostream& operator<<(ostream &os, f128 n){return os<<f64(n);}
#endif

template<typename T> Regular<T> operator+(const Regular<T>& a, const Regular<T>& b){return a.n+b.n;}
template<typename T> Regular<T> operator-(const Regular<T>& a, const Regular<T>& b){return a.n-b.n;}
template<typename T> Regular<T> operator*(const Regular<T>& a, const Regular<T>& b){return a.n*b.n;}
template<typename T> Regular<T> operator/(const Regular<T>& a, const Regular<T>& b){return a.n/b.n;}
template<typename T> Regular<T> operator%(const Regular<T>& a, const Regular<T>& b){return a.n%b.n;}
template<typename T> Regular<T> operator+=(Regular<T>& a, const Regular<T>& b){return a.n+=b.n;}
template<typename T> Regular<T> operator-=(Regular<T>& a, const Regular<T>& b){return a.n-=b.n;}
template<typename T> Regular<T> operator*=(Regular<T>& a, const Regular<T>& b){return a.n*=b.n;}
template<typename T> Regular<T> operator/=(Regular<T>& a, const Regular<T>& b){return a.n/=b.n;}
template<typename T> Regular<T> operator%=(Regular<T>& a, const Regular<T>& b){return a.n%=b.n;}
template<typename T> bool operator==(const Regular<T>& a, const Regular<T>& b){return a.n==b.n;}
template<typename T> Regular<T> operator^(const Regular<T>& a, const Regular<T>& b){return a.n^b.n;}
template<typename T> Regular<T> operator^=(Regular<T>& a, const Regular<T>& b){return a.n^=b.n;}

template<typename T> Regular<T> operator+(const Regular<T>& a, const T& b){return a.n+b;}
template<typename T> Regular<T> operator-(const Regular<T>& a, const T& b){return a.n-b;}
template<typename T> Regular<T> operator*(const Regular<T>& a, const T& b){return a.n*b;}
template<typename T> Regular<T> operator/(const Regular<T>& a, const T& b){return a.n/b;}
template<typename T> Regular<T> operator%(const Regular<T>& a, const T& b){return a.n%b;}
template<typename T> Regular<T> operator+=(Regular<T>& a, const T& b){return a.n+=b;}
template<typename T> Regular<T> operator-=(Regular<T>& a, const T& b){return a.n-=b;}
template<typename T> Regular<T> operator*=(Regular<T>& a, const T& b){return a.n*=b;}
template<typename T> Regular<T> operator/=(Regular<T>& a, const T& b){return a.n/=b;}
template<typename T> Regular<T> operator%=(Regular<T>& a, const T& b){return a.n%=b;}
template<typename T> bool operator==(const Regular<T>& a, const T& b){return a.n==b;}
template<typename T> Regular<T> operator^(const Regular<T>& a, const T& b){return a.n^b;}
template<typename T> Regular<T> operator^=(Regular<T>& a, const T& b){return a.n^=b;}

template<typename T> Regular<T> operator+(const T& a, const Regular<T>& b){return a+b.n;}
template<typename T> Regular<T> operator-(const T& a, const Regular<T>& b){return a-b.n;}
template<typename T> Regular<T> operator*(const T& a, const Regular<T>& b){return a*b.n;}
template<typename T> Regular<T> operator/(const T& a, const Regular<T>& b){return a/b.n;}
template<typename T> Regular<T> operator%(const T& a, const Regular<T>& b){return a%b.n;}
template<typename T> Regular<T> operator+=(T& a, const Regular<T>& b){return a+=b.n;}
template<typename T> Regular<T> operator-=(T& a, const Regular<T>& b){return a-=b.n;}
template<typename T> Regular<T> operator*=(T& a, const Regular<T>& b){return a*=b.n;}
template<typename T> Regular<T> operator/=(T& a, const Regular<T>& b){return a/=b.n;}
template<typename T> Regular<T> operator%=(T& a, const Regular<T>& b){return a%=b.n;}
template<typename T> bool operator==(const T& a, const Regular<T>& b){return a==b.n;}
template<typename T> Regular<T> operator^(const T& a, const Regular<T>& b){return a^b.n;}
template<typename T> Regular<T> operator^=(T& a, const Regular<T>& b){return a^=b.n;}

Bool operator^(const Bool& a, const Bool& b){return a.n^b.n;}
Bool operator^=(Bool& a, const Bool& b){return a.n^=b.n;}