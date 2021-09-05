#pragma once
#include "core/base.h"

// Formula:
// d[i][j]=min{i<k<j}(d[i][k]+d[k][j])+c[i][j]
// Constraints:
// c는 사각부등식{c[a][c]+c[b][d]≤c[a][d]+c[b][c] where a≤b≤c≤d}을 만족해야함
// Note:
Arr<Arr<i64>> knuth_opt(const Arr<i64>& init,
                        const function<i64(int, int)>& c) {
	int n = sz(init);
	Arr<Arr<i64>> dp(n + 1, Arr<i64>(n + 1));
	Arr<Arr<int>> a(n, Arr<int>(n + 1));
	for(int i = 0; i < n; i++) a[i][i + 1] = i;
	for(int d = 2; d <= n; d++)
		for(int i = 0; i <= n - d; i++) {
			dp[i][i + d] = inf<i64>();
			for(int k = a[i][i + d - 1]; k < a[i + 1][i + d]; k++) {
				if(dp[i][k + 1] + dp[k + 1][i + d] + c(i, i + d) < dp[i][i + d]) {
					dp[i][i + d] = dp[i][k + 1] + dp[k + 1][i + d] + c(i, i + d);
					a[i][i + d] = k;
				}
			}
		}
	return dp;
}

// Formula:
// d[i][j]=min{k<j}(d[i−1][k]+c[k][j])
// Constraints:
// a[t][i]는 d[t][i] Formula가 minimum이 되는 k들중 최소값이라 할때
// a[t][i]≤a[t][i+1]
// Note: c가 사각부등식을 만족하면 위 제약조건이 성립됨

// Codeground SCPC2016(2회) 본선1번 재활용
int n, m;
Arr<int> a;
Arr<Arr<int>> dp, c;

int& f(int i, int j) {
	static int _0 = 0, _inf = inf<int>();
	if(j == -1) return _0;
	if(i == -1) return _inf;
	return dp[i][j];
}

void dnc(int i, int s, int e, int ks, int ke) {
	int mid = (s + e) / 2, kk = ks;
	for(int k = ks; k < ke; k++)
		if(f(i, mid) > f(i - 1, k) + c[k + 1][mid])
			f(i, mid) = f(i - 1, k) + c[k + 1][mid], kk = k;
	if(e - s > 1) dnc(i, s, mid, ks, kk + 1), dnc(i, mid, e, kk, ke);
}

// signed main(){
// 	int t; cin>>t;
// 	for(int ti=1;ti<=t;ti++){
// 		cout<<"Case #"<<ti<<endl;
// 		cin>>n>>m;
// 		a=cinints(n);
// 		sort(all(a));
// 		dp=ARR(m,n,inf<int>());
// 		c=ARR(n,n,0ll);
// 		rep(i,n){
// 			int l=0,r=0;
// 			forci(j,0,i){
// 				l+=a[j];
// 				if((i-j+1)%2)
// 					l-=a[(i+j)/2];
// 				c[j][i]=r-l;
// 				if((i-j+1)%2)
// 					r+=a[(i+j)/2];
// 			}
// 		}
// 		rep(i,m) dnc(i,0,n,-1,n-1);
// 		cout<<dp[m-1][n-1]<<endl;
// 	}
// }