#pragma once
#include "core/base.h"

//legacy라서 검증필요
// Formula:
// d[i][j]=min{i<k<j}(d[i][k]+d[k][j])+c[i][j]
// Constraints:
// c는 사각부등식{c[a][c]+c[b][d]≤c[a][d]+c[b][c] where a≤b≤c≤d}을 만족해야함
Arr<Arr<i64>> knuth_opt(int n,const function<int(int,int)>& c){
	Arr<Arr<i64>> dp(n+1,Arr<i64>(n+1));
	Arr<Arr<int>> a(n,Arr<int>(n+1));
	for(int i=0;i<n;i++) a[i][i+1]=i;
	for(int d=2;d<=n;d++)
		for(int i=0;i<=n-d;i++){
			dp[i][i+d]=inf<i64>();
			for(int k=a[i][i+d-1];k<a[i+1][i+d];k++) {
				if(dp[i][k+1]+dp[k+1][i+d]+c(i,i+d)<dp[i][i+d]) {
					dp[i][i+d]=dp[i][k+1]+dp[k+1][i+d]+c(i, i+d);
					a[i][i+d]=k;
				}
			}
		}
	return dp;
}
