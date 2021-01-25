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
	T val;
};
