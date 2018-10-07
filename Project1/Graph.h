#pragma once
#include "Core.h"

struct Graph {
	static const int N = 1000;
	int n;
	vector<int> g[N];
	int in[N];

	Graph(int n) :n(n) {
		memset(in, 0, sizeof in);
	}

	void add_edge(int s, int e)
	{
		g[s].push_back(e);
		in[e]++;
	}

	vector<int> topo_sort()
	{
		queue<int> q;
		forh(i, 0, n)
			if (!in[i])
				q.push(i);
		vector<int> ret;
		while (q.size())
		{
			auto cur = q.front();
			ret.push_back(cur);
			q.pop();
			for (auto i : g[cur])
				if (--in[i] == 0)
					q.push(i);
		}
		reverse(ret.begin(), ret.end());
		forh(i, 0, n)
			if (in[i])
				return {};
		return ret;
	}
};