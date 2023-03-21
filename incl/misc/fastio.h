#pragma once

#define FASTIO
#include "core/abbr.h"
#include "core/arr.h"

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
	template<class T>FastCIN& operator>>(T& n){ignore_wsc();n=0;char neg=false;if(get()=='-')neg=true,pop();while('0'<=get()&&get()<='9')n=n*10+pop()-'0';if(neg)n*=-1;return *this;}//int,i64,Mod<mod>
	FastCIN& operator>>(char& c){ignore_wsc();c=pop();return *this;}
	FastCIN& operator>>(string& s){ignore_wsc();s.clear();while(get()!=' '&&get()!='\n'&&get())s.push_back(pop());return *this;}
	FastCIN& operator>>(fp& n){ignore_wsc();string s;while(('0'<=get()&&get()<='9')||get()=='.'||get()=='-')s.push_back(pop());n=stod(s);return *this;}
	template<class T> FastCIN& operator>>(Arr<T>& a){for(auto& i:a)*this>>i;return *this;}
	template<class T,class U> FastCIN& operator>>(pair<T,U>& a){*this>>a.fi>>a.se;return *this;}
}fcin;
#define cin fcin
