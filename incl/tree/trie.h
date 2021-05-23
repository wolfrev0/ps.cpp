#pragma once
#include "core/base.h"

template<class T,int n,char base=0> struct Trie{
	Trie(char ch=base,Trie* p=0):ch(ch),cnt(0),p(p){}
	Trie* next(char c){c-=base; return a[c]=a[c]?a[c]:new Trie<T,n,base>(c,this);}
	Trie* add(auto s,auto e){cnt++; return s^e?next(*s)->add(s+1,e):this;}
	void rem(auto s,auto e){cnt--;if(s^e)next(*s)->rem(s+1,e);}
	Trie* add(auto x){return add(x.begin(),x.end());}
	void rem(auto x){rem(x.begin(),x.end());}
	char ch;int cnt;Trie *p,*a[n]{};
};

//MSB to LSB, maxval=1e9(30bit)
struct Bitrie {
	Bitrie(char bit=0,Bitrie* p=0):bit(bit),cnt(0),p(p){}
	Bitrie* next(char bit){return a[bit]=a[bit]?a[bit]:new Bitrie(bit, this);}
	Bitrie* add(int x,int i=30){cnt++;return ~i?next(x>>i&1)->add(x,i-1):this;}
	void rem(int x,int i=30){cnt--;if(~i)next(x>>i&1)->rem(x,i-1);}
	int mex(int x,int i=30){
		if(!~i)return 0;
		if(next(x>>i&1)->cnt<(1<<i)) return next(x>>i&1)->mex(x,i-1);
		else return (1<<i)+next(x>>i&1^1)->mex(x,i-1);
	}
	char bit;int cnt;Bitrie *p,*a[2]{};
};