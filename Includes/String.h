#pragma once
#include "Core.h"

//a.k.a. partial match table, pi
vector<int> failure_function(const string &p) {
	vector<int> ret(p.size());
	int si = 1, pi = 0;
	while (si + pi < p.size()) {
		if (pi < p.size() && p[si + pi] == p[pi]) {
			pi++;
			ret[si + pi - 1] = pi;
		}
		else {
			if (!pi)
				++si;
			else {
				si += pi - ret[pi - 1];
				pi = ret[pi - 1];
			}
		}
	}
	return ret;
}

vector<int> kmp(const string &s, const string &p) {
	if (s.size() < p.size())
		return {};
	vector<int> ret;
	auto ff = failure_function(p);
	int si = 0, pi = 0;
	while (si <= s.size() - p.size()) {
		if (pi < p.size() && s[si + pi] == p[pi]) {
			if (++pi == p.size())
				ret.push_back(si);
		}
		else {
			if (!pi)
				++si;
			else {
				si += pi - ff[pi - 1];
				pi = ff[pi - 1];
			}
		}
	}

	return ret;
}

vector<int> failure_function2(const string &p) {
	int pi = 0;
	vector<int> ret(p.size());
	forh(i, 1, p.size()) {
		while (pi > 0 && p[i] != p[pi])
			pi = ret[pi - 1];
		if (p[i] == p[pi])
			ret[i] = ++pi;
	}
	return ret;
}

vector<int> kmp2(const string &s, const string &p) {
	const auto &ff = failure_function2(p);
	vector<int> ans(s.size());
	int pi = 0;
	forh(i, 0, s.size()) {
		while (pi > 0 && s[i] != p[pi])
			pi = ff[pi - 1];
		if (s[i] == p[pi] && (ans[i] = ++pi) == p.size())
		{
			pi = ff[pi - 1];
		}
	}
	return ans;
}

bool cmp(int i, int j, const vector<int> &g, int t){
	if(g[i]==g[j])
		return g[i+t] < g[j+t];
	return g[i]<g[j];
}

vector<int> suffix_array(const string &s){
	int n = s.size();
	vector<int> sa(n), ord(n+1), nord(n+1);
	forh(i, 0, s.size())
		sa[i]=i, ord[i]=s[i];
	
	ord[n]=-1;
	for(int i=1;i<n;i*=2){
		sort(sa.begin(), sa.end(), [&](const int &a, const int &b){return cmp(a, b, ord, i);});
		//This is O(N log N) but too high constant -> slower than O(N log^2 N)
		//counting_sort(sa, {[&](const int& x){return ord[min(i+x, (uint)n)];}});
		//counting_sort(sa, {[&](const int& x){return ord[x];}});

		nord[sa[0]]=0;
		nord[n]=-1;
		forh(j, 1, n)
			nord[sa[j]]=nord[sa[j-1]]+cmp(sa[j-1], sa[j], ord, i);
		ord=nord;
	}
	return sa;
}

//plzrun's code
vector<int> get_lcp(const string &s, const vector<int> &sa){
	int n = s.size();
	vector<int> lcp(n), psa(n+1), plcp(n+1);
    psa[sa[0]]=-1;
    forh(i, 1, n)
		psa[sa[i]]=sa[i-1];
	int common = 0;
    forh(i, 0, n) {
        if(psa[i]==-1)
			plcp[i]=0;
        else {
            while(s[i+common] == s[psa[i] + common]) 
				common++;
            plcp[i]=common;
            common = max(common-1,0);
        }
    }
    forh(i, 0, n)
		lcp[i]=plcp[sa[i]];
	return lcp;
}

//jh05013's code, O(NlogN)
vector<int> suffix_array2(const string &s){
    int n = s.size(), c = 0;
    vector<int> temp(n), pos2bckt(n), bckt(n), bpos(n), out(n);
    for(int i=0; i<n; i++) out[i] = i;
    sort(out.begin(), out.end(), [&](int a, int b){return s[a] < s[b];});
    for(int i=0; i<n; i++) {
        bckt[i] = c;
        if (i + 1 == n || s[out[i]] != s[out[i + 1]]) c++;
    }
    for (int h = 1; h < n && c < n; h <<= 1) {
        for (int i=0; i<n; i++) pos2bckt[out[i]] = bckt[i];
        for (int i=n-1; i>=0; i--) bpos[bckt[i]] = i;
        for (int i=0; i<n; i++) if (out[i] >= n-h)
            temp[bpos[bckt[i]]++] = out[i];
        for (int i=0; i<n; i++) if (out[i] >= h)
            temp[bpos[pos2bckt[out[i] - h]]++] = out[i] - h;
        c = 0;
        for (int i = 0; i + 1 < n; i++) {
            int a = (bckt[i] != bckt[i+1]) || (temp[i] >= n-h)
                    || (pos2bckt[temp[i+1]+h] != pos2bckt[temp[i]+h]);
            bckt[i] = c; c += a;
        }
        bckt[n - 1] = c++;
        temp.swap(out);
    }
    return out;
}

//comet's code
vector<int> get_lcp2(const string &s, const vector<int> &sa){
	int h=0;
	int n=s.size();
	vector<int> rank(n);
	forh(i, 0, sa.size())
		rank[sa[i]]=i;
	vector<int> lcp(n);
	forh(i,0,n){
		if(rank[i]){  
			int j=sa[rank[i]-1];  
			while(s[i+h]==s[j+h])
				h++;  
			lcp[rank[i]]=h;  
		}
		h -= !!h;
	}
	return lcp;
}
