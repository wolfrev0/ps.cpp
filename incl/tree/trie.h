#pragma once
#include "core/base.h"

//메모리 적당히 절약법: 배열대신 map, Ahocorasick2방법, 정렬후 이분탐색(채점번호 33273843), RadixTree
template<int n> struct Trie{
	struct Node{
		u32 cnt;
		array<u32,n> ch;
		Node(int cnt=0):cnt(cnt){ch.fill(-1);}
	};
	Arr<Node> a;
	Trie(){alloc();}
	void insert(auto s, auto e, u32 id=0){
		a[id].cnt++;
		if(s==e)
			return;
		if(!~transition(id,*s))
			transition(id,*s)=alloc();
		insert(s+1,e,transition(id,*s));
	}
	void remove(auto s, auto e, u32 id=0){
		a[id].cnt--;
		if(s==e)
			return;
		remove(s+1, e, transition(id,*s));
	}
private:
	u32 alloc(u32 cnt=0){
		a.emplace_back(cnt);
		return sz(a)-1;
	}
	u32& transition(u32 id, u32 x){return a[id].ch[x];}
};
template<int bit>
struct Bitrie:public Trie<2>{
	array<bool,bit> toArr(u64 x){
		array<bool,bit> xa;
		for(int i=0;i<bit;i++)
			xa[i]=x>>i&1;
		reverse(xa.begin(),xa.end());
		return xa;
	}
	void insert(u64 x){
		auto xa=toArr(x);
		Trie<2>::insert(xa.begin(),xa.end());
	}
	void remove(u64 x){
		auto xa=toArr(x);
		Trie<2>::remove(xa.begin(),xa.end());
	}
};