#pragma once
#include "Core.h"

struct Graph {
	vector<vector<int>> g;
	vector<int> in;

	Graph(int n) :g(n), in(n) {}

	inline void add_edge(int s, int e)
	{
		g[s].push_back(e);
		in[e]++;
	}

	vector<int> topo_sort()
	{
		queue<int> q;
		forh(i, 0u, g.size())
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
		forh(i, 0u, g.size())
			if (in[i])
				throw "Error";
		return ret;
	}

	vector<int> dijikstra()
	{
		return {};
	}

	vector<int> spfa()
	{
		return {};
	}
};