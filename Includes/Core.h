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
const f64 pi=acos(-1);
const f64 eps=1e-12;
const i32 prime=i32(2e9 + 11);
i32 mod=i32(1e9 + 7);
template<typename T> T inf() { return numeric_limits<T>::max() / 2; }
#define forh(var, s, e) for(int var=s; int(s)<=var && var<int(e); ++var)//for: half-opened range
#define forhi(var, s, e) for(int var=e-1; int(s)<=var && var<int(e); --var)//inversion
#define forho(var, s, e) int var=s; for(; int(s)<=var && var<int(e); ++var)//out declaration
#define forhoi(var, s, e) int var=e-1; for(; int(s)<=var && var<int(e); --var)
#define forc(var, s, e) for(int var=s; int(s)<=var && var<=int(e); ++var)//for: closed range
#define forci(var, s, e) for(int var=e; int(s)<=var && var<=int(e); --var)//inversion
#define forco(var, s, e) int var=s; for(; int(s)<=var && var<=int(e); ++var)//out declaration
#define forcoi(var, s, e) int var=e; for(; int(s)<=var && var<=int(e); --var)

string itos(int i){
  if(!i)
    return "0";
  string ret;
  while(i)
    ret.push_back(i%10+'0'), i/=10;
  reverse(ret.begin(), ret.end());
  return ret;
}

//Extensions
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/rope>
using namespace __gnu_pbds;
using namespace __gnu_cxx;

//Settings
