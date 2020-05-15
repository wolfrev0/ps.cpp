#pragma once 
#include "Core.h"

template<int n>
struct Trie{
	Trie(char ch):ch(ch),cnt(0){}
	Trie* next(char c){if(!a[c])a[c]=new Trie<n>(c);return a[c];}
	void add(auto s, auto e){
		cnt++;
		if(s==e)return;
		next(*s)->add(s+1,e);
	}
	char ch;
	int cnt;
private:
	Trie* a[n]{};
};
