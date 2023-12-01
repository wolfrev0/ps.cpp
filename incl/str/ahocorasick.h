#pragma once
#include "core/base.h"

// https://www.acmicpc.net/source/64889705
// Time: O(N)
// Memory: O(mN)
template<int m=26> struct AhoCorasick{
	struct Node{
		//parent_link, char from parent to here, suffix_link, output_link, successor
		u32 p,c,s=-1,o=-1,succ[m];
		Node():Node(0,-1){}
		Node(u32 p, u32 c):p(p),c(c){
			memset(succ,0xff,sizeof succ);
		}
	};
	Arr<Node> a={Node()};//root
	int alloc(){a.emplace_back();return sz(a)-1;}
	int alloc(u32 p, u32 c){a.emplace_back(p,c);return sz(a)-1;}
	u32& get_succ(u32 idx, u32 ch){
		return a[idx].succ[ch];
	}
	void add(u32 idx,auto its,auto ite){
		if(its==ite){
			a[idx].o=idx;
		}else{
			if(get_succ(idx,*its)==-1u)
				get_succ(idx,*its)=alloc(idx,*its);
			add(get_succ(idx,*its),its+1,ite);
		}
	}
	u32 transit(u32 idx, u32 ch){
		if(get_succ(idx,ch)!=-1u)
			return get_succ(idx,ch);
		if(a[idx].p==idx)
			return idx;
		return transit(get_slink(idx),ch);
	}
	u32 get_slink(u32 idx){
		if(a[idx].p==a[a[idx].p].p)
			return a[idx].p;
		if(a[idx].s==-1u)
			a[idx].s=transit(get_slink(a[idx].p),a[idx].c);
		return a[idx].s;
	}
	u32 get_olink(u32 idx){
		if(a[idx].p==idx) return idx;
		if(a[idx].o!=-1u) return a[idx].o;
		return a[idx].o=get_olink(get_slink(idx));
	}
};

// Memory Optimized AhoCorasick
// Time: O(mN)
// Memory: O(N)
template<int m=26> struct AhoCorasick2{
	struct Node{
		//parent_link, char from parent to here, suffix_link, output_link, successor
		u32 p=0,c=-1,s=-1,o=-1;
		Arr<pair<i32,u32>> succ;
		Node(){}
		Node(u32 p, u32 c):p(p),c(c){}
	};
	Arr<Node> a={Node()};//root
	int alloc(){a.emplace_back();return sz(a)-1;}
	int alloc(u32 p, u32 c){a.emplace_back(p,c);return sz(a)-1;}
	u32& get_succ(u32 idx, i32 ch){
		for(auto& [x,y]:a[idx].succ)
			if(x==ch)
				return y;
		return a[idx].succ.emplace_back(ch,-1).se;
	}
	void add(u32 idx,auto its,auto ite){
		if(its==ite){
			a[idx].o=idx;
		}else{
			if(get_succ(idx,*its)==-1u)
				get_succ(idx,*its)=alloc(idx,*its);
			add(get_succ(idx,*its),its+1,ite);
		}
	}
	u32 transit(u32 idx, i32 ch){
		if(get_succ(idx,ch)!=-1u)
			return get_succ(idx,ch);
		if(a[idx].p==idx)
			return idx;
		return transit(get_slink(idx),ch);
	}
	u32 get_slink(u32 idx){
		if(a[idx].p==a[a[idx].p].p)
			return a[idx].p;
		if(a[idx].s==-1u)
			a[idx].s=transit(get_slink(a[idx].p),a[idx].c);
		return a[idx].s;
	}
	u32 get_olink(u32 idx){
		if(a[idx].p==idx) return idx;
		if(a[idx].o!=-1u) return a[idx].o;
		return a[idx].o=get_olink(get_slink(idx));
	}
};

// incremental
// https://se.inf.ethz.ch/~meyer/publications/string/string_matching.pdf
// https://codeforces.com/blog/entry/10725
