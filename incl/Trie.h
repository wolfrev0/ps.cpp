#pragma once 
#include "Core.h"

template<int n, char base>
struct Trie{
	Trie(char ch):ch(ch),cnt(0){}
	Trie* next(char c){c-=base;if(!a[c])a[c]=new Trie<n,base>(c);return a[c];}
	void add(auto s, auto e){
		cnt++;
		if(s==e)return;
		next(*s)->add(s+1,e);
	}
	void add(string s){add(all(s));}
	char ch;
	int cnt;
private:
	Trie* a[n]{};
};
