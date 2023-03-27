//2022 scpc 2차 4번 (부분점수)
#include "core/base.h"

const int B=9;

void solve(){
	int n; cin>>n;
	short a[n][n];
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			cin>>a[i][j];
	int b0[B][B][1<<B][1<<B];//2d sparse table, min
	int b1[B][B][1<<B][1<<B];//2d sparse table, max
	memset(b0,0x3f,sizeof b0);
	memset(b1,0,sizeof b1);
	for(int l=0;l<B;l++)
		for(int k=0;k<B;k++)
			for(int i=0;i<n;i++)
				for(int j=0;j<n;j++){
					if(!l and !k){
						b0[k][l][i][j]=b1[k][l][i][j]=a[i][j];
					}else{
						b0[k][l][i][j]=min({
							k?b0[k-1][l][i][j]:inf<int>(),
							k?b0[k-1][l][i+(1<<k-1)][j]:inf<int>(),
							l?b0[k][l-1][i][j]:inf<int>(),
							l?b0[k][l-1][i][j+(1<<l-1)]:inf<int>(),
						});
						b1[k][l][i][j]=max({
							k?b1[k-1][l][i][j]:0ll,
							k?b1[k-1][l][i+(1<<k-1)][j]:0ll,
							l?b1[k][l-1][i][j]:0ll,
							l?b1[k][l-1][i][j+(1<<l-1)]:0ll,
						});
					}
				}
	int ans=0;
	for(int y0=0;y0<n;y0++)
		for(int x0=0;x0<n;x0++)
			for(int y1=y0;y1<n;y1++)
				for(int x1=x0;x1<n;x1++){
					int h=y1-y0+1, w=x1-x0+1;
					int lgh=flg2(h),lgw=flg2(w);
					int mx=max({
						b1[lgh][lgw][y0][x0],
						b1[lgh][lgw][y0][x1+1-(1<<lgw)],
						b1[lgh][lgw][y1+1-(1<<lgh)][x0],
						b1[lgh][lgw][y1+1-(1<<lgh)][x1+1-(1<<lgw)],
					});
					int mn=min({
						b0[lgh][lgw][y0][x0],
						b0[lgh][lgw][y0][x1+1-(1<<lgw)],
						b0[lgh][lgw][y1+1-(1<<lgh)][x0],
						b0[lgh][lgw][y1+1-(1<<lgh)][x1+1-(1<<lgw)],
					});
					ans += mx==mn+(y1-y0+1)*(x1-x0+1)-1;
					x1+=max<int>(0,(mx-(mn+(y1-y0+1)*(x1-x0+1)-1))/h-1);
				}
	println(ans);
}
