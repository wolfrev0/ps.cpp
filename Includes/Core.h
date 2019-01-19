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
#define endl '\n'
#define forh(var, begin, end) for(auto var=begin; begin<=var && var<decltype(begin)(end); ++var)//for: half-opened range
#define forhi(var, begin, end) for(auto var=end-1; decltype(end)(begin)<=var && var<end; --var)//inversion
#define forho(var, begin, end) auto var=begin; for(; begin<=var && var<decltype(begin)(end); ++var)//out declaration
#define forhoi(var, begin, end) auto var=end-1; for(; decltype(end)(begin)<=var && var<end; --var)
#define forc(var, begin, end) for(auto var=begin; begin<=var && var<=decltype(begin)(end); ++var)//for: closed range
#define forci(var, begin, end) for(auto var=end; decltype(end)(begin)<=var && var<=end; --var)//inversion
#define forco(var, begin, end) auto var=begin; for(; begin<=var && var<=decltype(begin)(end); ++var)//out declaration
#define forcoi(var, begin, end) auto var=end; for(; decltype(end)(begin)<=var && var<=end; --var)//inversion
#define trav(var, begin, cond) for(auto var=begin; cond; ++var)//travel
#define travo(var, begin, cond) auto var=begin; for(; cond; ++var)//out declaration

template<typename T>
struct Regular{
		T a;
		Regular(T a=0):a(a){}
		operator T()const{return a;}
		static T zero(){return 0;}
		static T one(){return 1;}
		static T inf(){return numeric_limits<T>::max()/2;}
};

#if __x86_64__ || __ppc64__
using i128 = __int128_t;
using u128 = __uint128_t;
using f128 = __float128;
template<>
struct Regular<i128>{
		i128 a;
		Regular(i128 a=0):a(a){}
		operator i128()const{return a;}
		static i128 zero(){return 0;}
		static i128 one(){return 1;}
		static i128 inf(){return ((u128(1)<<127)-1)/2;}
};
template<>
struct Regular<u128>{
		u128 a;
		Regular(u128 a=0):a(a){}
		operator u128()const{return a;}
		static u128 zero(){return 0;}
		static u128 one(){return 1;}
		static u128 inf(){return u128(-1)/2;}
};
template<>
struct Regular<f128>{
		f128 a;
		Regular(f128 a=0):a(a){}
		operator f128()const{return a;}
		static f128 zero(){return 0;}
		static f128 one(){return 1;}
		static f128 inf(){ return numeric_limits<f64>::max()/2; }
};
ostream& operator<<(ostream &os, u128 n){
	string s;while(n){ s.push_back(n%10+'0');n/=10; }
	reverse(s.begin(), s.end());
	return os<<s;
}
ostream& operator<<(ostream &os, i128 n){
  if(n<0){ os<<'-';n*=-1; }
	return os<<(u128)n;
}
ostream& operator<<(ostream &os, f128 n){return os<<(f64)n;}
#endif

//Extensions
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

//Settings
