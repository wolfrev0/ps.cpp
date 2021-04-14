#pragma once
#include "Core.h"

template<class T, int n, char base = 0> struct Trie {
	Trie(char ch = base, Trie* p = 0) : ch(ch), cnt(0), p(p) {}
	Trie* next(char c) {
		c -= base;
		if(!a[c]) a[c] = new Trie<T, n, base>(c, this);
		return a[c];
	}
	Trie* add(auto s, auto e) {
		cnt++;
		return s == e ? this : next(*s)->add(s + 1, e);
	}
	Trie* add(auto s) { return add(all(s)); }
	void rem(auto s, auto e) {
		cnt--;
		if(s != e) next(*s)->rem(s + 1, e);
	}
	void rem(auto s) { rem(all(s)); }
	char ch;
	int cnt;
	Trie *p, *a[n]{};
};

//MSB to LSB, maxval=1e9(30bit)
struct Bitrie {
	Bitrie(char bit=0, Bitrie* p=0) : bit(bit), cnt(0), p(p) {}
	Bitrie* next(char bit) {
		if(!a[bit]) a[bit] = new Bitrie(bit, this);
		return a[bit];
	}
	Bitrie* add(int x, int i=30){
		cnt++;
		return !~i ? this : next(x>>i&1)->add(x,i-1);
	}
	void rem(int x, int i=30) {
		cnt--;
		if(~i) next(x>>i&1)->rem(x,i-1);
	}

	int mex(int x, int i=30){
		if(i==-1) return 0;
		if(next(x>>i&1)->cnt<(1<<i)) return next(x>>i&1)->mex(x,i-1);
		else return (1<<i)+next(x>>i&1^1)->mex(x,i-1);
	}

	char bit;
	int cnt;
	Bitrie *p, *a[2]{};
};