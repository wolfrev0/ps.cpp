#pragma once
#include "Core.h"
//WARNING: Should be included after FastIO.h

template<class T>ostream& operator<<(ostream& s, const Arr<T>& a) {for(auto i:a) cout<<i<<' '; return s;}
int cinint(){int x;cin>>x;return x;}
char cinchr(){char x;cin>>x;return x;}
Arr<int> cinints(int n){Arr<int> a(n);for(auto&i:a)cin>>i;return a;}

#if C20
	template<class... A> void _cin_(A&... a) { ((cin>>a),...); }
	#define CIN(T,...) T __VA_ARGS__; _cin_(__VA_ARGS__);
	template<class... A> void _cout_(A... a) { ((cout<<a<<' '),...); }
	#define COUT(...) _cout_(__VA_ARGS__), cout<<endl;
	template<class T> T dupl(const T& x, int n){ T r; rep(_,n)r.insert(r.end(),all(x)); return r; }
#endif