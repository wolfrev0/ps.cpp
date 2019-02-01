#pragma once
#include "Core.h"

template<typename T>
struct FenwickTree{
	int n;
	FenwickTree(int n):n(n+1), tree(n+2){}
	vector<T> tree;

	T query(int s, int e){
		s++, e++;//ft idx base = 1
		return sum(e-1)-sum(s-1);
	}

	void update(int i, T delta){
		i++;
		while(i<n){
			tree[i]+=delta;
			i+=(i&-i);
		}
	}

private:
	T sum(int i){
		T ans=0;
		while(i>0){
			ans+=tree[i];
			i-=(i&-i);
		}
		return ans;
	}
};

template<typename T>
struct SegmentTree{
	SegmentTree(int n, 
	const function<T(const T&,const T&)> &queryf=[](const T& a, const T& b){return a+b;}, 
	const function<T(const T&,const T&)> &updf=[](const T& a, const T& b){return a+b;}, 
	const T& init_val=0):n(n),queryf(queryf),updf(updf),init_val(init_val),tree(2*n, init_val){}

	void update(int p, T value) {
		p+=n;
		for (tree[p] = updf(tree[p], value); p > 1; p >>= 1)
			tree[p >> 1] = queryf(tree[p], tree[p ^ 1]);
	}
	
	T query(int begin, int end) {
		T res = init_val;
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
	const T init_val;
	vector<T> tree;
};

//upperbound of 2^(ceil(log2(n))+1)/n is 4. (plot floor(2^(ceil(log2(x))+1)/x) from x=0 to 100000000)
template<typename T>
struct SegmentTreeLazy
{
	SegmentTreeLazy(
		int n, T id_qry, T id_upd,
		const function<T(const T&, const T&)>& queryf,
		const function<T(const T&, const T&, int)>& updf,
		const function<T(const T&, const T&)>& propaf)
		:n(n), id_qry(id_qry), id_upd(id_upd), queryf(queryf), updf(updf), propaf(propaf), tree(4*n, id_upd), lazy(4*n, id_upd)
	{}
	SegmentTreeLazy(int n=0)
		:n(n), id_qry(id_qry), id_upd(id_upd),
		queryf([](T a, T b) {return a + b; }),
		updf([](T tval, T lval, int cnt) {return tval + lval * cnt; }),
		propaf([](T lval, T val) { return lval + val; }),
		tree(4*n, id_upd), lazy(4*n, id_upd)
	{}

	void update(int p, T val) { update_range(1, 0, n, p, p+1, val); }
	void update(int s, int e, T val) { update_range(1, 0, n, s, e, val); }
	T query(int s, int e) { return query2(1, 0, n, s, e); }
private:
	const int n;
	const T id_qry, id_upd;
	const function<T(const T&, const T&)> queryf;
	const function<T(const T&, const T&, int)> updf;
	const function<T(const T&, const T&)> propaf;
	vector<T> tree;
	vector<T> lazy;

	void update_lazy(int cur, int cs, int ce) {
		if (lazy[cur] != id_upd) {
			tree[cur] = updf(tree[cur], lazy[cur], ce-cs);
			if (ce-cs>1) {
				lazy[cur * 2] = propaf(lazy[cur * 2], lazy[cur]);
				lazy[cur * 2 + 1] = propaf(lazy[cur * 2 + 1], lazy[cur]);
			}
			lazy[cur] = id_upd;
		}
	}

	void update_range(int cur, int cs, int ce, int s, int e, T val) {
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
			return id_qry;
		if (s <= cs && ce <= e)
			return tree[cur];
		return queryf(query2(cur * 2, cs, (cs + ce) / 2, s, e), query2(cur * 2 + 1, (cs + ce) / 2, ce, s, e));
	}
};