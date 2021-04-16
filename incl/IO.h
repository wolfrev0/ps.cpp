#pragma once
#include "Core.h"

#if !(DEBUG)&&!(INTERACTIVE)
struct FIO {
	static const int BUF_SZ = 1 << 24;
	char *p, *q;
	FIO() {
		p = new char[BUF_SZ];
		q = p + BUF_SZ;
		cin.read(p, BUF_SZ);
	}
	char get() {
		if(p == q) cin.read(p -= BUF_SZ, BUF_SZ);
		return *p++;
	}
	operator bool() { return *p; }

	FIO& operator>>(char& c) {
		do { c = get(); } while(c == ' ' || c == '\n');
		return *this;
	}
	template<typename T> FIO& operator>>(T& n) {
		n = 0;
		bool neg = false;
		int c = get();
		while(c == ' ' || c == '\n') c = get();
		if(c == '-') {
			neg = true;
			c = get();
		}
		while('0' <= c && c <= '9') n = n * 10 + c - '0', c = get();
		if(neg) n *= -1;
		return *this;
	}
	FIO& operator>>(string& s) {
		int c = get();
		while(c == ' ' || c == '\n') c = get();
		while(c && c != ' ' && c != '\n') {
			s.pushb(c);
			c = get();
		}
		return *this;
	}
} fcin;
#define cin fcin
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
