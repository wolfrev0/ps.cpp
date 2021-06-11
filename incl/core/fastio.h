#pragma once
#define FASTIO

struct FastCIN:public istream{
	static const int SZ=1<<22;
	unsigned cnt=0;char a[SZ],*p;
	FastCIN(){preload();}
	int preload(){cin.read(p=a,SZ);return cnt=cin.gcount();}
	inline char pop(){if(!cnt)preload(); return cnt>0?cnt--,*p++:0;}
	inline char get(){if(!cnt)preload(); return cnt>0?*p:0;}
	void ignore_wsc(){while(get()==' '||get()=='\n')pop();}
	operator bool(){return get();}
	FastCIN& operator>>(int& n){ignore_wsc();n=0;char neg=false;if(get()=='-')neg=true,pop();while('0'<=get()&&get()<='9')n=n*10+pop()-'0';if(neg)n*=-1;return *this;}
	FastCIN& operator>>(char& c){ignore_wsc();c=pop();return *this;}
	FastCIN& operator>>(string& s){ignore_wsc();s.clear();while(get()!=' '&&get()!='\n'&&get())s.pushb(pop());return *this;}
	FastCIN& operator>>(f64& n){ignore_wsc();string s;while('0'<=get()&&get()<='9'||get()=='.'||get()=='-')s.pushb(pop());n=stod(s);return *this;}
};
