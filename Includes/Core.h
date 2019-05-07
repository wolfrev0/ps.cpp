#pragma once
#ifndef DEBUG
  #pragma GCC optimize ("Ofast")
#endif
#include <bits/stdc++.h>
using namespace std;

//Extensions: gp_hash_table, XSet
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

//Extensions: rope
#include <ext/rope>
using namespace __gnu_cxx;

//Syntax Sugars
#define forh(var, s, e) for(int var=s; int(s)<=var && var<int(e); ++var)//for: half-opened range
#define forhi(var, s, e) for(int var=e-1; int(s)<=var && var<int(e); --var)//inversion
#define forho(var, s, e) int var=s; for(; int(s)<=var && var<int(e); ++var)//out declaration
#define forhoi(var, s, e) int var=e-1; for(; int(s)<=var && var<int(e); --var)
#define forc(var, s, e) for(int var=s; int(s)<=var && var<=int(e); ++var)//for: closed range
#define forci(var, s, e) for(int var=e; int(s)<=var && var<=int(e); --var)//inversion
#define forco(var, s, e) int var=s; for(; int(s)<=var && var<=int(e); ++var)//out declaration
#define forcoi(var, s, e) int var=e; for(; int(s)<=var && var<=int(e); --var)
#define rep(x) forh(repi,0,x)
#define all(x) x.begin(),x.end()
#define sum_in(s,e) accumulate(s,e,0ll)
//NOTE: *mri(it) == *prev(it)
#define mri(it) make_reverse_iterator(it)

using f64 = double;
using i64=long long;
using u64=unsigned long long;
const f64 pi=acos(-1);
const f64 eps=1e-12;
const int prime=998244353;//1073741783 1073741789 int(2e9+11) int(1e9+9)
int mod=int(1e9+7);
template<typename T> T inf() { return numeric_limits<T>::max() / 2; }
template<typename C, typename RI> RI rerase(C& c, RI ri){return next(mri(c.erase(prev(ri.base()))));}
