#pragma once
#ifndef DEBUG
    #pragma GCC optimize ("Ofast")
#endif
#include <bits/stdc++.h>

//Syntax Sugars
using namespace std;
using ld = double;
using ll = long long;
using ull = unsigned long long;
using uint = unsigned; 
using ushort = unsigned short;
using uchar = unsigned char;
const int mod = int(1e9 + 7);
const int prime = int(2e9 + 11);
const ld pi = acos(-1);
const ld eps = 1e-12;
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
constexpr inline T inf() { return numeric_limits<T>::max() / 2; }
template<typename T, typename U>
inline pair<T, U> operator+(const pair<T, U> &a, const pair<T, U> &b) { return { a.first + b.first, a.second + b.second }; }
template<typename T, typename U>
inline pair<T, U> operator+=(pair<T, U> &a, const pair<T, U> &b) { return a = a + b; }
template<typename T, typename U>
inline pair<T, U> operator-(const pair<T, U> &a, const pair<T, U> &b) { return { a.first - b.first, a.second - b.second }; }
template<typename T, typename U>
inline pair<T, U> operator-=(pair<T, U> &a, const pair<T, U> &b) { return a = a - b; }
#if __x86_64__ || __ppc64__
using lll = __int128_t;
using ulll = __uint128_t;
ostream& operator<<(ostream &os, lll n){
    if(n<0){
        os<<'-';
        n*=-1;
    }
	string s;
	while(n){
		s.push_back(n%10+'0');
		n/=10;
	}
	reverse(s.begin(), s.end());
	return os<<s;
}
ostream& operator<<(ostream &os, ulll n){
	string s;
	while(n){
		s.push_back(n%10+'0');
		n/=10;
	}
	reverse(s.begin(), s.end());
	return os<<s;
}
#endif

//Extensions
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

//Settings
using ScalarType = ll;
