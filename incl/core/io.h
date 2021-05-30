#pragma once
#include "core/base.h"
static_assert(!INTERACTIVE);

struct FIO{
	static const int SZ=1<<22;
	unsigned cnt=0;char a[SZ],*p;
	FIO(){preload();}
	int preload(){cin.read(p=a,SZ);return cnt=cin.gcount();}
	inline char pop(){if(!cnt)preload(); return cnt>0?cnt--,*p++:0;}
	inline char get(){if(!cnt)preload(); return cnt>0?*p:0;}
	void ignore_wsc(){while(get()==' '||get()=='\n')pop();}
	operator bool(){return get();}
	template<typename T>
	FIO& operator>>(T& n){ignore_wsc();n=0;char neg=false;if(get()=='-')neg=true,pop();while('0'<=get()&&get()<='9')n=n*10+pop()-'0';if(neg)n*=-1;return *this;}
	FIO& operator>>(char& c){ignore_wsc();c=pop();return *this;}
	FIO& operator>>(string& s){ignore_wsc();s.clear();while(get()!=' '&&get()!='\n')s.pushb(pop());return *this;}
};
struct PrettyIO:FIO{
	template<class T=int>T tok(){T x;*this>>x;return x;}
	template<class T=int>Arr<T> toks(int n){Arr<T> a(n);for(auto& i:a)*this>>i;return a;}
	template<class... A> void _read(A&...a){((*this>>a),...);}
}_pcin;
#define cin _pcin

template<class T> ostream& operator<<(ostream& s,const Arr<T>& a){for(auto i:a)cout<<i<<' ';return s;}
#define READ(T,...) T __VA_ARGS__;cin._read(__VA_ARGS__);
template<class... A> void PRINT(A...a){((cout<<a<<' '),...,(cout<<endl));}