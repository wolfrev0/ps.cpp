#pragma once

#include "Core.h"

template<typename T>
struct SegmentTree
{
	SegmentTree(
		int n,
		T id = 0,
		function<T(T, T)> segf = [](T a, T b) {return a + b; },
		function<T(int, int, T, T)> lazyf = [](int l, int r, T tval, T lval) {return tval + lval*(r - l + 1); },
		function<T(T, T)> propaf = [](T lval, T val) { return lval + val; },
		T lazy_null = 0)
		//upperbound of 2^(ceil(log2(n))+1)/n is 4
		:n(n), id(id), segf(segf), lazyf(lazyf), propaf(propaf), lazy_null(lazy_null),
		tree(4 * n, id), lazy(4 * n, lazy_null)
	{}
	const int n;
	const T id;
	const function<T(T, T)> segf;
	const function<T(int, int, T, T)> lazyf;
	const function<T(T, T)> propaf;
	const T lazy_null;

	vector<T> tree;
	vector<T> lazy;

	void update(int p, T val) { update_range(1, 0, n - 1, p, p, val); }
	void update(int l, int r, T val) { update_range(1, 0, n - 1, l, r, val); }
	T query(int l, int r) { return query2(1, 0, n - 1, l, r); }
private:
	void update_lazy(int cur, int cl, int cr)
	{
		if (lazy[cur] != lazy_null)
		{
			tree[cur] = lazyf(cl, cr, tree[cur], lazy[cur]);
			if (cl != cr)
			{
				lazy[cur * 2] = propaf(lazy[cur*2], lazy[cur]);
				lazy[cur * 2 + 1] = propaf(lazy[cur * 2 + 1], lazy[cur]);
			}
			lazy[cur] = lazy_null;
		}
	}

	void update_range(int cur, int cl, int cr, int l, int r, T val)
	{
		update_lazy(cur, cl, cr);
		if (l > cr || r < cl)
			return;
		if (l <= cl && cr <= r)
		{
			lazy[cur] = propaf(lazy[cur], val);
			update_lazy(cur, cl, cr);
			return;
		}
		update_range(cur * 2, cl, (cl + cr) / 2, l, r, val);
		update_range(cur * 2 + 1, (cl + cr) / 2 + 1, cr, l, r, val);
		tree[cur] = segf(tree[cur * 2], tree[cur * 2 + 1]);
	}

	T query2(int cur, int cl, int cr, int l, int r)
	{
		update_lazy(cur, cl, cr);
		if (l > cr || r < cl)
			return id;
		if (l <= cl && cr <= r)
			return tree[cur];
		return segf(query2(cur * 2, cl, (cl + cr) / 2, l, r), query2(cur * 2 + 1, (cl + cr) / 2 + 1, cr, l, r));
	}
};