#pragma once
#include "bits/stdc++.h"
#define endl '\n'
#define forh(var, begin, end) for(auto var = begin; var < end; ++var)//for: half-opened range
#define forhi(var, begin, end) for(auto var = end-1; var >= begin; --var)//inversion
#define forc(var, begin, end) for(auto var = begin; var <= end; ++var)//for: closed range
#define forci(var, begin, end) for(auto var = end; var >= begin; --var)//inversion
#define trav(var, begin, cond) for(auto var = begin; cond; ++var)//travel
#pragma GCC optimize ("Ofast")

using namespace std;
using namespace std::placeholders;

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
const int dir[4][2] = { { 1, 0 },{ 0, 1 },{ -1, 0 },{ 0, -1 } };

template<typename T>
constexpr inline T inf() { return numeric_limits<T>::max() / 2; }