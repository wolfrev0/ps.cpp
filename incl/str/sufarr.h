#pragma once
#include "core/base.h"

bool cmp(int i, int j, const Arr<int> &g, int t) {
	if(g[i] == g[j]) return g[i + t] < g[j + t];
	return g[i] < g[j];
}

// sa[i]: 사전순으로 i번째인 접미사의 시작인덱스
template<class T> Arr<int> suffix_array(const Str<T> &s) {
	int n = sz(s);
	Arr<int> sa(n), ord(n + 1), nord(n + 1);
	for(int i = 0; i < sz(s); i++) sa[i] = i, ord[i] = s[i];

	ord[n] = -1;
	for(int i = 1; i < n; i *= 2) {
		sort(sa.begin(), sa.end(),
		     [&](const int &a, const int &b) { return cmp(a, b, ord, i); });
		nord[sa[0]] = 0;
		nord[n] = -1;
		for(int j = 1; j < n; j++)
			nord[sa[j]] = nord[sa[j - 1]] + cmp(sa[j - 1], sa[j], ord, i);
		ord = nord;
	}
	return sa;
}

// lcp[i]: 사전순 i번째 접미사와 i−1번째 접미사의 가장 긴 공통 접두사의 길이
// based on plzrun's code
template<class T> Arr<int> get_lcp(const Str<T> &s, const Arr<int> &sa) {
	int n = sz(s);
	Arr<int> lcp(n), psa(n + 1), plcp(n + 1);
	psa[sa[0]] = -1;
	for(int i = 1; i < n; i++) psa[sa[i]] = sa[i - 1];
	int common = 0;
	for(int i = 0; i < n; i++) {
		if(psa[i] == -1) plcp[i] = 0;
		else {
			while(s[i+common]==s[psa[i]+common])common++;
			plcp[i]=common;
			common=max<int>(common-1,0);
		}
	}
	for(int i = 0; i < n; i++) lcp[i] = plcp[sa[i]];
	return lcp;
}

// based on jh05013's code, O(NlogN)
template<class T> Arr<int> suffix_array2(const Str<T> &s) {
	int n = sz(s), c = 0;
	Arr<int> temp(n), pos2bckt(n), bckt(n), bpos(n), out(n);
	for(int i = 0; i < n; i++) out[i] = i;
	sort(out.begin(), out.end(), [&](int a, int b) { return s[a] < s[b]; });
	for(int i = 0; i < n; i++) {
		bckt[i] = c;
		if(i + 1 == n || s[out[i]] != s[out[i + 1]]) c++;
	}
	for(int h = 1; h < n && c < n; h <<= 1) {
		for(int i = 0; i < n; i++) pos2bckt[out[i]] = bckt[i];
		for(int i = n - 1; i >= 0; i--) bpos[bckt[i]] = i;
		for(int i = 0; i < n; i++)
			if(out[i] >= n - h) temp[bpos[bckt[i]]++] = out[i];
		for(int i = 0; i < n; i++)
			if(out[i] >= h) temp[bpos[pos2bckt[out[i] - h]]++] = out[i] - h;
		c = 0;
		for(int i = 0; i < n - 1; i++) {
			int a = bckt[i] != bckt[i + 1] || temp[i] >= n - h ||
			        pos2bckt[temp[i + 1] + h] != pos2bckt[temp[i] + h];
			bckt[i] = c;
			c += a;
		}
		bckt[n - 1] = c++;
		temp.swap(out);
	}
	return out;
}

// based on comet's code
template<class T> Arr<int> get_lcp2(const Str<T> &s, const Arr<int> &sa) {
	int h = 0;
	int n = sz(s);
	Arr<int> rank(n);
	for(int i = 0; i < sz(sa); i++) rank[sa[i]] = i;
	Arr<int> lcp(n);
	for(int i = 0; i < n; i++) {
		if(rank[i]) {
			int j = sa[rank[i] - 1];
			while(s[i + h] == s[j + h]) h++;
			lcp[rank[i]] = h;
		}
		h -= !!h;
	}
	return lcp;
}