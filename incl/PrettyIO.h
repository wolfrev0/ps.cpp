#pragma once
#include "Core.h"
#if FAST_IO
#include "FastIO.h"
#endif

template<class... A> void _cin_(A&... a) { ((cin >> a), ...); }
template<class... A> void _cout_(A... a) { ((cout << a << ' '), ...); }
template<class T> ostream& operator<<(ostream& s, const Arr<T>& a) {
	for(auto i : a) cout << i << ' ';
	return s;
}
#define CIN(T, ...) \
	T __VA_ARGS__;    \
	_cin_(__VA_ARGS__);
#define COUT(...) _cout_(__VA_ARGS__), cout << endl;

template<class T=int>
T geti() {
	T x;
	cin >> x;
	return x;
}
template<class T=int>
Arr<T> getis(int n) {
	Arr<T> a(n);
	for(auto& i : a) cin >> i;
	return a;
}
