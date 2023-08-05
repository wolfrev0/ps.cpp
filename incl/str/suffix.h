#pragma once
#include "core/base.h"

// Suffix Array
// sa[i]: 사전순으로 i번째인 접미사의 시작인덱스
template<class T> Arr<int> suffix_array(const Str<T> &s) {
	// O(N log^2 N)
	int n = sz(s);
	Arr<int> sa(n), ord(n + 1), nord(n + 1);
	for(int i = 0; i < sz(s); i++) sa[i] = i, ord[i] = s[i];

	func(bool,cmp,int i, int j, int t) {
		if(ord[i] == ord[j]) return ord[i + t] < ord[j + t];
		return ord[i] < ord[j];
	};

	ord[n] = -1;
	for(int i = 1; i < n; i *= 2) {
		sort(sa.begin(), sa.end(),
		     [&](const int &a, const int &b) { return cmp(a, b, i); });
		nord[sa[0]] = 0;
		nord[n] = -1;
		for(int j = 1; j < n; j++)
			nord[sa[j]] = nord[sa[j - 1]] + cmp(sa[j - 1], sa[j], i);
		ord = nord;
	}
	return sa;
}
template<class T> Arr<int> suffix_array_opt(const Str<T> &s) {
	// based on jh05013's code, O(NlogN)
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
// lcp[i]: 사전순 i번째 접미사와 i−1번째 접미사의 가장 긴 공통 접두사의 길이
template<class T> Arr<int> get_lcp(const Str<T> &s, const Arr<int> &sa) {
	// based on plzrun's code
	int n = sz(s);
	Arr<int> lcp(n), psa(n + 1), plcp(n + 1);
	psa[sa[0]] = -1;
	for(int i = 1; i < n; i++) psa[sa[i]] = sa[i - 1];
	int common = 0;
	for(int i = 0; i < n; i++) {
		if(psa[i] == -1) plcp[i] = 0;
		else {
			while(s[i+common]==s[psa[i]+common])
				common++;
			plcp[i]=common;
			common=max<int>(common-1,0);
		}
	}
	for(int i = 0; i < n; i++)
		lcp[i] = plcp[sa[i]];
	return lcp;
}

// Suffix Automaton(DAG)
// Suffix Tree = SuffixAutomaton(reversed(str)).suffix_links
// https://cp-algorithms.com/string/suffix-automaton.html
template<signed m>
struct SuffixAutomaton{
	struct Node{
		signed len, link;
		array<signed,m> next;
		Node(signed len, signed link):
			len(len),
			link(link){
			fill(next.begin(),next.end(),-1);
		}
	};
	Arr<Node> a;
	signed last=0;
	SuffixAutomaton():a(1,Node(0,-1)){}
	signed& transition(signed from, signed c){
		return a[from].next[c];
	}
	void add(signed c){
		a.emplace_back(a[last].len+1,0);
		int cur=sz(a)-1;
		int p=last;
		while(p!=-1 and transition(p,c)==-1){
			transition(p,c)=cur;
			p=a[p].link;
		}
		if(p!=-1){
			int q=transition(p,c);
			if(a[p].len+1==a[q].len){
				a[cur].link=q;
			}else{
				int r=sz(a);
				a.emplace_back(a[q]);
				a[r].len=a[p].len+1;
				a[cur].link=a[q].link=r;
				while(p!=-1 and transition(p,c)==q){
					transition(p,c)=r;
					p=a[p].link;
				}
			}
		}
		last=cur;
	}
};
// Memory Optimized SuffixAutomaton
// Time:O(26N)
// Memory:O(N)
// for(int i=0;i<26;i++)transition(x,i)
// 이렇게 쓰면 26개 다 생겨서 도루묵이므로
// for(auto [x,y]:sa.a[x].next)transition(x,i)
// 이렇게 쓰자
// https://www.acmicpc.net/source/64612686
template<signed m>
struct SuffixAutomaton2{
	struct Node{
		signed len, link;
		Arr<pair<signed,signed>> next;
		Node(signed len, signed link):
			len(len),
			link(link){
		}
	};
	Arr<Node> a;
	signed last=0;
	SuffixAutomaton2():a(1,Node(0,-1)){}
	signed& transition(signed from, signed c){
		for(auto& [x,y]:a[from].next)
			if(x==c)
				return y;
		return a[from].next.emplace_back(c,-1).se;
	}
	void add(signed c){
		a.emplace_back(a[last].len+1,0);
		int cur=sz(a)-1;
		int p=last;
		while(p!=-1 and transition(p,c)==-1){
			transition(p,c)=cur;
			p=a[p].link;
		}
		if(p!=-1){
			int q=transition(p,c);
			if(a[p].len+1==a[q].len){
				a[cur].link=q;
			}else{
				int r=sz(a);
				a.emplace_back(a[q]);
				a[r].len=a[p].len+1;
				a[cur].link=a[q].link=r;
				while(p!=-1 and transition(p,c)==q){
					transition(p,c)=r;
					p=a[p].link;
				}
			}
		}
		last=cur;
	}
};

// Suffix Tree
// Suffix Automaton의 suffix link로 구성할 수 있는건 rev(str)의 suffix tree이므로
// incremental하게 suffix tree를 관리해야하면 ukkonen써야할듯?
// 다만, 많은 경우 부분문자열에 대한것을 풀때 str의 suffix tree인지 rev(str)의 suffix tree인지 상관없는 경우가 많아서 왠만하면 필요없을것 같다.
// https://codeforces.com/blog/entry/16780
// https://en.wikipedia.org/wiki/Ukkonen%27s_algorithm
