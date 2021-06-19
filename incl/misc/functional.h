#pragma once 
#include "core/base.h"

template<class T>T dupl(const T& x, int n) {T r;while(n--)r.insert(r.end(), x.begin(),x.end());return r;}
Arr<int> range(int n){Arr<int> r;while(n--)r.emplb(sz(r));return r;}
template<class T>Arr<pair<int,T>> enumerate(Arr<T>& a){Arr<pair<int,T>> r;for(auto&i:a)r.emplb(sz(r),i);return r;}