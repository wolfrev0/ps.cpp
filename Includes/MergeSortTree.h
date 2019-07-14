#pragma once
#include "Core.h"

struct MergeSortTree{
	MergeSortTree(int n)
	:n(n), tree(4*n){}

	MergeSortTree(const vector<int>& v):MergeSortTree(sz(v)){build(1, 0, n, v);}

	//void update(int p, int val) {update2(1, 0, n, p, val);}
	int query(int s, int e, int k) {return query2(1, 0, n, s, e, k);}
private:
	const int n;
	vector<vector<int>> tree;

	void build(int cur, int cs, int ce, const vector<int>& v) {
		if(ce-cs==1){
			tree[cur].pb(v[cs]);
			return;
		}
		build(cur * 2, cs, (cs + ce) / 2, v);
		build(cur * 2 + 1, (cs + ce) / 2, ce, v);
		tree[cur].resize(ce-cs);
		merge(all(tree[cur*2]), all(tree[cur*2+1]), tree[cur].begin());
	}

	// void update2(int cur, int cs, int ce, int p, int val) {
	// 	if (p >= ce || p < cs)
	// 		return;
	//   if(ce-cs==1){
	//     if(tree[cur].size())
	//       tree[cur].erase(tree[cur].begin());
	//     tree[cur].insert(val);
	//     return;
	//   }
	// 	update2(cur * 2, cs, (cs + ce) / 2, p, val);
	// 	update2(cur * 2 + 1, (cs + ce) / 2, ce, p, val);
	// 	tree[cur] = tree[cur * 2];
	//   for(auto i:tree[cur * 2 + 1])
	//     tree[cur].insert(i.first);
	// }

	int query2(int cur, int cs, int ce, int s, int e, int k) {
		if (s >= ce || e <= cs)
			return 0;
		if (s <= cs && ce <= e){
			return ce-cs - distance(tree[cur].begin(), upper_bound(all(tree[cur]), k));
		}
		return query2(cur * 2, cs, (cs + ce) / 2, s, e, k) + query2(cur * 2 + 1, (cs + ce) / 2, ce, s, e, k);
	}
};