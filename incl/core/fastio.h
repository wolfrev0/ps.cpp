#pragma once

#define FASTIO
#include "core/abbr.h"
#include "core/arr.h"

//INPUT
struct FastCIN{
	static const int SZ=1<<24;
	unsigned cnt=0;char a[SZ+1],*p;
	FastCIN(){preload();}
	void tie(int x){}
	int preload(){return cnt=cin.read(p=a,SZ).gcount();}
	inline char pop(){if(!cnt)preload(); return cnt>0?cnt--,*p++:0;}
	inline char get(){if(!cnt)preload(); return cnt>0?*p:0;}
	void ignore_wsc(){while(get()==' '||get()=='\n')pop();}
	operator bool(){return get();}
	template<class T>FastCIN& operator>>(T& n){ignore_wsc();n=0;char neg=false;if(get()=='-')neg=true,pop();while('0'<=get()&&get()<='9')n=n*10+pop()-'0';if(neg)n*=-1;return *this;}
	FastCIN& operator>>(char& c){ignore_wsc();c=pop();return *this;}
	FastCIN& operator>>(string& s){ignore_wsc();s.clear();while(get()!=' '&&get()!='\n'&&get())s.pushb(pop());return *this;}
	FastCIN& operator>>(f64& n){ignore_wsc();string s;while(('0'<=get()&&get()<='9')||get()=='.'||get()=='-')s.pushb(pop());n=stod(s);return *this;}
	template<class T> FastCIN& operator>>(Arr<T>& a){for(auto& i:a)*this>>i;return *this;}
	template<class T,class U> FastCIN& operator>>(pair<T,U>& a){*this>>a.fi>>a.se;return *this;}
};

struct TokCIN:public FastCIN{
	static TokCIN* x;
	static TokCIN* instance(){return !x?x=new TokCIN():x;}
	template<class T=i64>T tok(){T x;operator>>(x);return x;}
	template<class T=i64>Arr<T> toks(int n){Arr<T> a(n);for(auto& i:a)operator>>(i);return a;}
	template<class... A> void _read(A&...a){((operator>>(a)),...);}
};
TokCIN* TokCIN::x;
#define cin (*TokCIN::instance())
#define READ(T,...) T __VA_ARGS__;cin._read(__VA_ARGS__);

//OUTPUT
template<class T> ostream& operator<<(ostream& s,const Arr<T>& a){for(auto i:a)cout<<i<<' ';return s;}
template<class... A> void PRINT(A...a){((cout<<a<<' '),...,(cout<<endl));}

//