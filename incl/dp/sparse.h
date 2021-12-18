#pragma once
#include "core/base.h"
#include "math/monoid.h"

//길이처리나 온라인추가 필요하면 직접 짜자(20931)
template<class M>
struct SparseTable{
	using T=M::T;
	SparseTable(int n,int m):n(n),m(m),dp(ARR(m,n,M::id())){}
	~SparseTable(){WARN(!_build,"SparseTable not builded");}
	bool _build=false;
	void build(){
		_build=true;
		for(int i=1;i<m;i++)
			for(int j=0;j<n;j++)
				dp[i][j]=M::f(dp[i][j],dp[i-1][dp[i-1][j]]);
	}
	void set(int x,int y,int val){dp[y][x]=val;}
	int get(int x,int y){return dp[y][x];}
	int kth(int x,i64 k){
		for(int i=0;i<m;i++)
			if(k>>i&1)
				x=dp[i][x];
		return x;
	}
	int n,m;
	Arr<Arr<T>> dp;
};
