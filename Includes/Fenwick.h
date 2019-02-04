#pragma once
#include "Core.h"

template<typename T>
struct FenwickTree{
	int n;
	FenwickTree(int n):n(n+1), tree(n+2, T::zero()){}
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
		T ans=T::zero();
		while(i>0){
			ans+=tree[i];
			i-=(i&-i);
		}
		return ans;
	}
};