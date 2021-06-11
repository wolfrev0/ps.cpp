#pragma once

//Handy Funcs
template<class T>int sz(const T& x){return x.size();}
template<class T>cxp T inf(){return numeric_limits<T>::max()/2;}
int divc(int a,int b){if(b<0)a=-a,b=-b;return (a>0)?(a+b-1)/b:a/b;}
int divf(int a,int b){if(b<0)a=-a,b=-b;return (a>0)?a/b:(a-b+1)/b;}
cxp int lg2f(int x){return 63-__builtin_clzll(x);}
cxp int lg2c(int x){return 64-__builtin_clzll(x-1);}
template<class T>inline T sq(T x){return x*x;}
bool assmin(auto& a,auto&& b){return a>b?a=b,true:false;}
bool assmax(auto& a,auto&& b){return a<b?a=b,true:false;}
int argmin(const auto& a){return min_element(a.begin(),a.end())-a.begin();}
int argmax(const auto& a){return max_element(a.begin(),a.end())-a.begin();}