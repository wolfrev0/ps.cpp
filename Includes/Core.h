#pragma once

#ifndef DEBUG
    #pragma GCC optimize ("Ofast")
#endif

#include <bits/stdc++.h>

//syntax sugars
#define endl '\n'
#define forh(var, begin, end) for(auto var = begin; var < end; ++var)//for: half-opened range
#define forhi(var, begin, end) for(auto var = end-1; var >= begin; --var)//inversion
#define forho(var, begin, end) auto var = begin; for(; var < end; ++var)//out declaration
#define forc(var, begin, end) for(auto var = begin; var <= end; ++var)//for: closed range
#define forci(var, begin, end) for(auto var = end; var >= begin; --var)//inversion
#define forco(var, begin, end) auto var = begin; for(; var <= end; ++var)//out declaration
#define trav(var, begin, cond) for(auto var = begin; cond; ++var)//travel
#define travo(var, begin, cond) auto var = begin; for(; cond; ++var)//out declaration

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

template<typename T, typename U>
inline pair<T, U> operator+(const pair<T, U> &a, const pair<T, U> &b) { return { a.first + b.first, a.second + b.second }; }
template<typename T, typename U>
inline pair<T, U> operator+=(pair<T, U> &a, const pair<T, U> &b) { return a = a + b; }
template<typename T, typename U>
inline pair<T, U> operator-(const pair<T, U> &a, const pair<T, U> &b) { return { a.first - b.first, a.second - b.second }; }
template<typename T, typename U>
inline pair<T, U> operator-=(pair<T, U> &a, const pair<T, U> &b) { return a = a - b; }

template<typename T>
inline void counting_sort(vector<T>& v, const function<T(T)> &f = [](const T& x){return x;})
{
	const int MAX_BW = 500001;
	static vector<T> bucket[MAX_BW+1];
	for(auto &i:bucket)
		i.clear();

    T m = inf<T>(), M = -inf<T>();
    for(auto &i:v){
        m = min(m, f(i));
        M = max(M, f(i));
    }

    for(auto i:v)
        bucket[f(i) - m].push_back(i);
    v.clear();
    forc(i, 0, M-m)
        for(auto j:bucket[i])
            v.push_back(j);
}