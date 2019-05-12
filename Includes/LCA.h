#pragma once
#include "RootedTree.h"
#include "Seg.h"

template<typename T>
struct LCA:public RootedTree<T>{
	using P=RootedTree<T>;

	LCA(const Tree<T>& t, int r)
	:P(t, r), st(n*2), lpos(n)
	{int segi=0; dfs_lca(r, segi);}

	int lca(int a, int b){
		int l=lpos[a], r=lpos[b];
		if(l>r)
			swap(l, r);
		return st.query(l, r+1).idx;
	}
protected:
	using P::n;
	using P::r;
	using P::parent;
	using P::children;
	struct LCA_T{
		int ord=0x7fffffff/2, idx=-1;
		bool operator<(const LCA_T& r)const{return ord<r.ord;}
		bool operator==(const LCA_T& r)const{return ord==r.ord && idx==r.idx;}
	};
	struct SegLCA:public Seg<LCA_T>{
		SegLCA(int n):Seg<LCA_T>(n){}
		LCA_T q(const LCA_T& a, const LCA_T& b)override{return min(a,b);};
		LCA_T upd(const LCA_T& a, const LCA_T& b)override{return b;};
	};

	SegLCA st;
	vector<int> lpos;

	void dfs_lca(int cur, int& segi){
		int ord = segi;
		lpos[cur]=ord;
		st.update(segi++, {ord, cur});

		for(const auto& i:children[cur]){
			dfs_lca(i.e, segi);
			st.update(segi++, {ord, cur});
		}
	}
};