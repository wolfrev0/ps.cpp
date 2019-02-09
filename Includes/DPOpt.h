#pragma once
#include "Core.h"

vector<vector<i64>> knuth_opt(const vector<i64>& init, const function<i64(int,int)>& c){
  int n=init.size();
  vector<vector<i64>> dp(n+1,vector<i64>(n+1));
  vector<vector<int>> a(n,vector<int>(n+1));
  forh(i, 0, n)
    a[i][i+1]=i;
  forc(d, 2, n){
    forc(i, 0, n-d){
      dp[i][i+d]=inf<i64>();
      forc(k, a[i][i+d-1], a[i+1][i+d]){
        if(dp[i][k+1] + dp[k+1][i+d]+c(i,i+d) < dp[i][i+d]){
          dp[i][i+d]=dp[i][k+1] + dp[k+1][i+d]+c(i,i+d);
          a[i][i+d]=k;
        }
      }
    }
  }
  return dp;
}