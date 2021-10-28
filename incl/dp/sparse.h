#pragma once
#include "core/base.h"

//길이처리나 온라인추가 필요하면 직접 짜자(20931)
struct SparseTable{
	SparseTable(const Arr<int>& p):n(sz(p)),dp(ARR(61,n,0ll)){
		dp[0]=p;
		for(int i=1;i<=60;i++)
			for(int j=0;j<n;j++)
				dp[i][j]=dp[i-1][dp[i-1][j]];
	}
	int kth(int x,i64 k){
		for(int i=0;i<=60;i++)
			if(k>>i&1)
				x=dp[i][x];
		return x;
	}
	int n;
	Arr<Arr<int>> dp;
};
