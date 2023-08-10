#pragma once
#include "core/base.h"

// https://www.acmicpc.net/source/64889705
template<int m=26> struct AhoCorasick{
	struct Node{
		//parent_link, suffix_link, output_link, successor
		signed p=0,s=-1,o=-1,succ[m];
		bool is_out=false;
		Node(){
			memset(succ,0xff,sizeof succ);
		}
	};
	Arr<Node> a={Node()};//root
	signed& get_succ(signed idx, signed ch){
		return a[idx].succ[ch];
	}
	signed get_ch(signed x){
		for(int i=0;i<m;i++)
			if(get_succ(a[x].p,i)==x)
				return i;
		return -1;
	}
	void add(signed idx,auto its,auto ite){
		if(its==ite){
			a[idx].is_out=true;
			a[idx].o=idx;
		}else{
			if(get_succ(idx,*its)==-1){
				get_succ(idx,*its)=sz(a);
				a.emplace_back();
				a[get_succ(idx,*its)].p=idx;
			}
			add(get_succ(idx,*its),its+1,ite);
		}
	}
	signed transit(signed idx, signed ch){
		if(get_succ(idx,ch)!=-1)
			return get_succ(idx,ch);
		if(a[idx].p==idx)
			return idx;
		return transit(get_slink(idx),ch);
	}
	signed get_slink(signed idx){
		if(a[idx].p==a[a[idx].p].p)
			return a[idx].p;
		if(a[idx].s==-1)
			a[idx].s=transit(get_slink(a[idx].p),get_ch(idx));
		return a[idx].s;
	}
	signed get_olink(signed idx){
		if(a[idx].p==idx) return idx;
		if(a[idx].is_out) return idx;
		if(a[idx].o!=-1) return a[idx].o;
		return a[idx].o=get_olink(get_slink(idx));
	}
};

// Memory Optimized AhoCorasick
// Time:O(26N)
// Memory:O(N)
template<int m=26> struct AhoCorasick2{
	struct Node{
		//parent_link, suffix_link, output_link, successor
		signed p=0,s=-1,o=-1;
		Arr<pair<signed,signed>> succ;
		bool is_out=false;
		Node(){}
	};
	Arr<Node> a={Node()};//root
	signed& get_succ(signed idx, signed ch){
		for(auto& [x,y]:a[idx].succ)
			if(x==ch)
				return y;
		return a[idx].succ.emplace_back(ch,-1).se;
	}
	signed get_ch(signed x){
		for(int i=0;i<m;i++)
			if(get_succ(a[x].p,i)==x)
				return i;
		return -1;
	}
	void add(signed idx,auto its,auto ite){
		if(its==ite){
			a[idx].is_out=true;
			a[idx].o=idx;
		}else{
			if(get_succ(idx,*its)==-1){
				get_succ(idx,*its)=sz(a);
				a.emplace_back();
				a[get_succ(idx,*its)].p=idx;
			}
			add(get_succ(idx,*its),its+1,ite);
		}
	}
	signed transit(signed idx, signed ch){
		if(get_succ(idx,ch)!=-1)
			return get_succ(idx,ch);
		if(a[idx].p==idx)
			return idx;
		return transit(get_slink(idx),ch);
	}
	signed get_slink(signed idx){
		if(a[idx].p==a[a[idx].p].p)
			return a[idx].p;
		if(a[idx].s==-1)
			a[idx].s=transit(get_slink(a[idx].p),get_ch(idx));
		return a[idx].s;
	}
	signed get_olink(signed idx){
		if(a[idx].p==idx) return idx;
		if(a[idx].is_out) return idx;
		if(a[idx].o!=-1) return a[idx].o;
		return a[idx].o=get_olink(get_slink(idx));
	}
};

// incremental
// https://se.inf.ethz.ch/~meyer/publications/string/string_matching.pdf
// https://codeforces.com/blog/entry/10725