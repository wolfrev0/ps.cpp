#pragma once
#include "core/base.h"

//메모리 적당히 절약: 배열대신 map, 포인터대신 index
//메모리 갈아엎는 절약: 1.정렬후 이분탐색(채점번호 33273843), 2.RadixTree
template<int n> struct Trie{
	Trie(char c=0,Trie* p=0):c(c),cnt(0),p(p){}
	~Trie(){for(auto i:a)if(i)delete i;}
	Trie* add(auto s,auto e){
		cnt++;return s^e?next(*s)->add(s+1,e):this;
	}
	void rem(auto s,auto e){cnt--;if(s^e)a[*s]->rem(s+1,e);}
	char c;int cnt;Trie *p,*a[n]{};
};

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wchar-subscripts"
#pragma GCC diagnostic ignored "-Wparentheses"
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
#pragma GCC diagnostic pop