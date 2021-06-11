#pragma once

#ifdef FASTIO
struct TokCIN:FastCIN{
	template<class T=int>T tok(){T x;*this>>x;return x;}
	template<class T=int>Arr<T> toks(int n){Arr<T> a(n);for(auto& i:a)*this>>i;return a;}
	template<class... A> void _read(A&...a){((*this>>a),...);}
}tokcin;
#define cin tokcin
#define READ(T,...) T __VA_ARGS__;cin._read(__VA_ARGS__);
#endif
template<class T> ostream& operator<<(ostream& s,const Arr<T>& a){for(auto i:a)cout<<i<<' ';return s;}
template<class... A> void PRINT(A...a){((cout<<a<<' '),...,(cout<<endl));}