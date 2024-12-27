#pragma once
#include "core.h"
#include "math/struct/monoid.h"
#include "graph/functional.h"

//BOJ20931같이 업데이트 필요한건 어떻게?
//BOJ12008(USACO262144)같이 중간에 값 들어가는건?
template<Monoid M, i32 m=62>
struct SparseTable{
	using T=decltype(M::id());
	explicit SparseTable(const FunctionalGraph& fg):n(fg.n),dp(ARR(n,m,M::id())){
		for(int i=0;i<n;i++)
			dp[i][0]=fg[i];
		for(int j=1;j<m;j++)
			for(int i=0;i<n;i++)
				dp[i][j]=M::f(dp[i][j],dp[dp[i][j-1]][j-1]);
	}
	T kth(int x,i64 k){
		for(int i=m-1;i>=0;i--)
			if(k>>i&1)
				x=dp[x][i];
		return x;
	}
	i32 n;
	Arr<Arr<T>> dp;
};