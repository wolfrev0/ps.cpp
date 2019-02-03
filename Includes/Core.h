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
#define forcoi(var, begin, end) int var=end; for(; (int)begin<=var && var<=(int)end; --var)
#define trav(var, begin, cond) for(int var=begin; cond; ++var)//travel
#define travo(var, begin, cond) int var=begin; for(; cond; ++var)//out declaration

//Extensions
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

//Settings
