#pragma once

#include "Core.h"

template<typename T>
struct SegmentTree{
	const int n;
	const function<T(T,T)> f;
	const T init_val;
	vector<T> tree;

	SegmentTree(int n, const function<T(T,T)> &f=[](T a, T b){return a+b;}, const T &init_val=0):n(n),f(f),init_val(init_val),tree(2*n, init_val){}

	void modify(int p, T value) {
		for (tree[p += n] = value; p > 1; p >>= 1)
			tree[p >> 1] = f(tree[p], tree[p ^ 1]);
	}
	
	//half opened interval [begin, end)
	T query(int begin, int end) {
		T res = init_val;
		for (begin += n, end += n; begin < end; begin >>= 1, end >>= 1) {
			if (begin & 1) res = f(res, tree[begin++]);
			if (end & 1) res = f(res, tree[--end]);
		}
		return res;
	}
};

template<typename T>
struct SegmentTreeLazy
{
	SegmentTreeLazy(
		int n,
		T id,
		const function<T(T, T)>& segf,
		const function<T(int, int, T, T)>& lazyf,
		const function<T(T, T)>& propaf,
		T lazy_null = inf<int>())
		//upperbound of 2^(ceil(log2(n))+1)/n is 4
		:n(n), id(id), segf(segf), lazyf(lazyf), propaf(propaf), lazy_null(lazy_null),
		tree(4 * n, id), lazy(4 * n, lazy_null)
	{}
	SegmentTreeLazy(
		int n,
		T lazy_null = inf<int>(),
		T id = 0)
		//upperbound of 2^(ceil(log2(n))+1)/n is 4
		:n(n), id(id), segf([](T a, T b) {return a + b; }), lazy_null(lazy_null),
		tree(4 * n, id), lazy(4 * n, lazy_null), 
		lazyf([lazy_null, id](int l, int r, T tval, T lval) {return tval + (lval != lazy_null ? lval : id) * (r - l + 1); }),
		propaf([lazy_null, id](T lval, T val) { return (lval != lazy_null ? lval : id) + val; })
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
	void update_lazy(int cur, int cl, int cr) {
		if (lazy[cur] != lazy_null) {
			tree[cur] = lazyf(cl, cr, tree[cur], lazy[cur]);
			if (cl != cr) {
				lazy[cur * 2] = propaf(lazy[cur * 2], lazy[cur]);
				lazy[cur * 2 + 1] = propaf(lazy[cur * 2 + 1], lazy[cur]);
			}
			lazy[cur] = lazy_null;
		}
	}

	void update_range(int cur, int cl, int cr, int l, int r, T val) {
		update_lazy(cur, cl, cr);
		if (l > cr || r < cl)
			return;
		if (l <= cl && cr <= r) {
			lazy[cur] = propaf(lazy[cur], val);
			update_lazy(cur, cl, cr);
			return;
		}
		update_range(cur * 2, cl, (cl + cr) / 2, l, r, val);
		update_range(cur * 2 + 1, (cl + cr) / 2 + 1, cr, l, r, val);
		tree[cur] = segf(tree[cur * 2], tree[cur * 2 + 1]);
	}

	T query2(int cur, int cl, int cr, int l, int r) {
		update_lazy(cur, cl, cr);
		if (l > cr || r < cl)
			return id;
		if (l <= cl && cr <= r)
			return tree[cur];
		return segf(query2(cur * 2, cl, (cl + cr) / 2, l, r), query2(cur * 2 + 1, (cl + cr) / 2 + 1, cr, l, r));
	}
};