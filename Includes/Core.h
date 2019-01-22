#pragma once
#ifndef DEBUG
    #pragma GCC optimize ("Ofast")
#endif
#include <bits/stdc++.h>

//Syntax Sugars
using namespace std;
using f64 = double;
using i8=char;using i16=short;using i32=int;using i64=long long;
using u8=unsigned char;using u16=unsigned short;using u32=unsigned;using u64=unsigned long long;
const i32 prime=i32(2e9 + 11);
const f64 pi=acos(-1);
const f64 eps=1e-12;
i32 mod=i32(1e9 + 7);
#define forh(var, begin, end) for(int var=begin; (int)begin<=var && var<(int)end; ++var)//for: half-opened range
#define forhi(var, begin, end) for(int var=end-1; (int)begin<=var && var<(int)end; --var)//inversion
#define forho(var, begin, end) int var=begin; for(; (int)begin<=var && var<(int)end; ++var)//out declaration
#define forhoi(var, begin, end) int var=end-1; for(; (int)begin<=var && var<(int)end; --var)
#define forc(var, begin, end) for(int var=begin; (int)begin<=var && var<=(int)end; ++var)//for: closed range
#define forci(var, begin, end) for(int var=end; (int)begin<=var && var<=(int)end; --var)//inversion
#define forco(var, begin, end) int var=begin; for(; (int)begin<=var && var<=(int)end; ++var)//out declaration
#define forcoi(var, begin, end) int var=end; for(; (int)begin<=var && var<=(int)end; --var)//inversion
#define trav(var, begin, cond) for(int var=begin; cond; ++var)//travel
#define travo(var, begin, cond) int var=begin; for(; cond; ++var)//out declaration

template<typename T>
struct Regular{
		T n;
		Regular(T n=0):n(n){}
		operator T()const{return n;}
		static T zero(){return 0;}
		static T one(){return 1;}
		static T inf(){return numeric_limits<T>::max()/2;}
};
template<typename T>
ostream& operator<<(ostream &os, Regular<T> n){return os<<n.n;}
template<typename T>
istream& operator>>(istream &is, Regular<T> &n){return is>>n.n;}
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
		static i128 zero(){return 0;}
		static i128 one(){return 1;}
		static i128 inf(){return ((u128(1)<<127)-1)/2;}
};
template<>
struct Regular<u128>{
		u128 n;
		Regular(u128 n=0):n(n){}
		operator u128()const{return n;}
		static u128 zero(){return 0;}
		static u128 one(){return 1;}
		static u128 inf(){return u128(-1)/2;}
};
template<>
struct Regular<f128>{
		f128 n;
		Regular(f128 n=0):n(n){}
		operator f128()const{return n;}
		static f128 zero(){return 0;}
		static f128 one(){return 1;}
		static f128 inf(){ return numeric_limits<f64>::max()/2; }
};
using I128=Regular<i128>; using U128=Regular<u128>; using F128=Regular<f128>;
ostream& operator<<(ostream &os, u128 n){
	string s;while(n){ s.push_back(n%10+'0');n/=10; }
	reverse(s.begin(), s.end());
	return os<<s;
}
ostream& operator<<(ostream &os, i128 n){
  if(n<0){ os<<'-';n*=-1; }
	return os<<(u128)n;
}
ostream& operator<<(ostream &os, f128 n){return os<<f64(n);}
#endif

//Extensions
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

//Settings
