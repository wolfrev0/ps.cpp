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