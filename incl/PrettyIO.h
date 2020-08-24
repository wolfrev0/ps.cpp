#pragma once
#include "Core.h"
//WARNING: Should be included after FastIO.h

template<typename T>ostream& operator<<(ostream& s, const Arr<T>& a) {for(auto i:a) cout<<i<<' '; return s;}
auto cinint(){int x;cin>>x;return x;}
auto cinchr(){char x;cin>>x;return x;}
auto cinints(int n){Arr<int> a(n);for(auto&i:a)cin>>i;return a;}