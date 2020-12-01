#pragma once
#include "Core.h"
//WARNING: Should be included after FastIO.h

template<class T>ostream& operator<<(ostream& s, const Arr<T>& a) {for(auto i:a) cout<<i<<' '; return s;}
int cinint(){int x;cin>>x;return x;}
char cinchr(){char x;cin>>x;return x;}
Arr<int> cinints(int n){Arr<int> a(n);for(auto&i:a)cin>>i;return a;}