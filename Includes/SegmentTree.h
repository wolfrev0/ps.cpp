#pragma once
#include "Core.h"

template<typename T>
struct SegmentTree{
	SegmentTree(int n, 
	const function<T(const T&,const T&)> &queryf=[](const T& a, const T& b){return a+b;}, 
	const function<T(const T&,const T&)> &updf=[](const T& a, const T& b){return a+b;})
	:n(n),queryf(queryf),updf(updf),tree(2*n, T::zero()){}

	void update(int p, T value) {
		p+=n;
		for (tree[p] = updf(tree[p], value); p > 1; p >>= 1)
			tree[p >> 1] = queryf(tree[p], tree[p ^ 1]);
	}
	
	//use commutative law (definitly, with associative law)
	T query(int begin, int end) {
		T res = T::zero();
		for (begin += n, end += n; begin < end; begin >>= 1, end >>= 1) {
			if (begin & 1) res = queryf(res, tree[begin++]);
			if (end & 1) res = queryf(res, tree[--end]);
		}
		return res;
	}

private:
	const int n;
	const function<T(const T&, const T&)> queryf;
	const function<T(const T&, const T&)> updf;
	vector<T> tree;
};

//upperbound of 2^(ceil(log2(n))+1)/n is 4. (plot floor(2^(ceil(log2(x))+1)/x) from x=0 to 100000000)
template<typename T, typename U=T>
struct SegmentTreeLazy
{
	SegmentTreeLazy(
	int n,
	const function<T(const T&, const T&)>& queryf,
	const function<T(const T&, const U&, int)>& updf,
	const function<U(const U&, const U&)>& propaf)
	:n(n), queryf(queryf), updf(updf), propaf(propaf), tree(4*n, T::zero()), lazy(4*n, U::zero())
	{}
	SegmentTreeLazy(int n=0)
	:SegmentTreeLazy(n, [](T a, T b) {return a+b; }, [](T tval, U lval, int cnt) {return tval+lval*cnt;}, [](U lval, U val) {return lval+val;})
	{}

	void update(int p, U val) {update_range(1, 0, n, p, p+1, val);}
	void update(int s, int e, U val) {update_range(1, 0, n, s, e, val);}
	T query(int s, int e) {return query2(1, 0, n, s, e);}
private:
	const int n;
	const function<T(const T&, const T&)> queryf;
	const function<T(const T&, const U&, int)> updf;
	const function<U(const U&, const U&)> propaf;
	vector<T> tree;
	vector<U> lazy;

	void update_lazy(int cur, int cs, int ce) {
		if (lazy[cur] != U::zero()) {
			tree[cur] = updf(tree[cur], lazy[cur], ce-cs);
			if (ce-cs>1) {
				lazy[cur * 2] = propaf(lazy[cur * 2], lazy[cur]);
				lazy[cur * 2 + 1] = propaf(lazy[cur * 2 + 1], lazy[cur]);
			}
			lazy[cur] = U::zero();
		}
	}

	void update_range(int cur, int cs, int ce, int s, int e, U val) {
		update_lazy(cur, cs, ce);
		if (s >= ce || e <= cs)
			return;
		if (s <= cs && ce <= e) {
			lazy[cur] = propaf(lazy[cur], val);
			update_lazy(cur, cs, ce);
			return;
		}
		update_range(cur * 2, cs, (cs + ce) / 2, s, e, val);
		update_range(cur * 2 + 1, (cs + ce) / 2, ce, s, e, val);
		tree[cur] = queryf(tree[cur * 2], tree[cur * 2 + 1]);
	}

	T query2(int cur, int cs, int ce, int s, int e) {
		update_lazy(cur, cs, ce);
		if (s >= ce || e <= cs)
			return T::zero();
		if (s <= cs && ce <= e)
			return tree[cur];
		return queryf(query2(cur * 2, cs, (cs + ce) / 2, s, e), query2(cur * 2 + 1, (cs + ce) / 2, ce, s, e));
	}
};